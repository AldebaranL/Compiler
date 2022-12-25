#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <deque>
using namespace std;

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;

int ret_label;
Operand *ret_ope;
Operand *ret_dst;
int times=0;

bool ret_alarm=false;

Operand *const_1 = new Operand(new ConstantSymbolEntry(TypeSystem::intType, 1));
Operand *const_0=new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0));


Node::Node()
{
    seq = counter++;
}

void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb, bool branch)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
        //dynamic_cast 强制类型转换操作符
            if(branch)
                dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
            else
                dynamic_cast<CondBrInstruction*>(inst)->setFalseBranch(bb);
        else if(inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode()
{
    cout<<"functiondef~!"<<endl;
    cout<<se->toStr()<<endl;
    Unit *unit = builder->getUnit();
    Function *func = new Function(unit, se); 

    // BasicBlock* ret_bb = new BasicBlock(func);
    // std::vector<BasicBlock*>::iterator endblock=func->end();
    // new UncondBrInstruction((BasicBlock*)(*endblock), ret_bb);
    // cout<<"bb_num: "<<ret_bb->getNo()<<endl;
    // new StoreInstruction(ret_ope, ret_dst, ret_bb);
    // new RetInstruction(ret_ope,ret_bb);
    
    //???
    func->ret_bb=new BasicBlock(func);
    
    BasicBlock *entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.
    builder->setInsertBB(entry);

    //处理返回值 为返回值分配空间
    SymbolEntry *addr_se;
    Type *type, *ret_type;
    
    ret_type=((FunctionType*)(se->getType()))->getRetType();
    bool isvoid=(ret_type->isVoid());
    type = new PointerType(ret_type);

    //设置返回值label
    ret_label=SymbolTable::getLabel();
    addr_se = new TemporarySymbolEntry(type, ret_label);//新建地址
    TemporarySymbolEntry* ret_se=new TemporarySymbolEntry(ret_type, ret_label);//为返回值新建地址
    ret_dst = new Operand(addr_se);

    //cout<<"ret_dst:"<<ret_dst->toStr()<<endl;
    //cout<<"addr_se:"<<addr_se->getType()->toStr()<<endl;
    if(!isvoid)
        entry->insertFront(new AllocaInstruction(ret_dst,ret_se)); 

    // 增加：处理参数列表
    if(!paramlist.empty()){
       for(unsigned int i = 0;i < paramlist.size();i++)
       {
            //cout<<"paramlist~!"<<endl;
            IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(paramlist[i]->getSymPtr());
            Instruction *alloca;
            Operand *addr;
            SymbolEntry *addr_se;
            Type *type;
            type = new PointerType(se->getType());
            addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());//新建地址
            addr = new Operand(addr_se);
            
            //为形参分配空间
            alloca = new AllocaInstruction(addr, se); 
            entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block. 
            Operand *ope=paramlist[i]->getOperand();
            func->op.push_back(ope);//存储每个形参的地址
            BasicBlock* bb = builder->getInsertBB();
            new StoreInstruction( addr,ope, bb);//存储形参
            se->setAddr(addr);
            //cout<<se<<endl;
            //cout<<"addr:"<<se->getAddr()->toStr()<<endl;
       }
    }

    stmt->genCode();
    
    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo ok
    */
   //建立控制流图
    //cout<<"blocknum: "<<func->getBlockList().size()<<endl;
    //遍历当前function中的每个block
    //cout<<"-----------------------size="<<func->begin()-func->end()<<endl;
    int no;
    bool f=false;
    BasicBlock* bf=nullptr;
    for(std::vector<BasicBlock*>::iterator block=func->begin();block!=func->end();block++)
    {
        //cout<<"block"<<(*block)->getNo()<<endl;
        if((*block)->empty()){
            fprintf(stderr,"%d\n",(*block)->getNo());
        }
        Instruction * inst = (*block)->rbegin();
        //将每个块的最后一个指令（分支跳转指令）的后续块与当前的块之间的边连接好
        if(inst->isCond())
        {
            //条件跳转指令，后续有两个块
            BasicBlock * trueBB = ((CondBrInstruction*) inst)->getTrueBranch();
            //trueBB->output();
            //cout<<trueBB->getNo()<<endl;
            BasicBlock * falseBB = ((CondBrInstruction*) inst)->getFalseBranch();
            //cout<<falseBB->getNo()<<endl;
            //todo!!!
            //new CondBrInstruction(trueBB,falseBB,,(*block));
            if(!trueBB->empty()){
                (*block)->addSucc(trueBB);
                trueBB->addPred(*block);
            }
            if(!falseBB->empty()){
            (*block)->addSucc(falseBB);
            falseBB->addPred(*block);
            }
        }
        else if(inst->isUncond()){
            //无条件跳转指令，后续有1个块
            BasicBlock * next = ((UncondBrInstruction*) inst)->getBranch();
            ////todo!!!new UncondBrInstruction(next,(*block));
            //next->output();
            //cout<<next->getNo()<<endl;
            //cout<<next->empty()<<endl;
            if(!next->empty()){
                (*block)->addSucc(next);
                next->addPred(*block);
            }
        }
        else{
            // cout<<func->getSymPtr()->toStr()<<endl;
            // cout<<"block:"<<(*block)->getNo()<<endl;
            // cout<<"empty?"<<((*block)->empty())<<endl;
            // if(isvoid){
            //     //(*block)->insertBack(new UncondBrInstruction(func->getRet(), (*block)));
            // }
            //是否为空
            if((*block)->empty()){//为空 ret_bb的no设为此
                f=true;
                no=(*block)->getNo();
            }
            else{
                f=false;
                bf=(*block);
            }
            // cout<<"neither!"<<endl;

        }
        //cout<<"getNumOfPred"<<(*block)->getNumOfPred()<<endl;
        //cout<<"getNumOfSucc"<<(*block)->getNumOfSucc()<<endl;
    }
    
    type = new PointerType(ret_type);
    int ld_label=SymbolTable::getLabel();
    addr_se = new TemporarySymbolEntry(type, ld_label);//新建地址
    TemporarySymbolEntry* ld_se = new TemporarySymbolEntry(ret_type, ld_label);
    Operand* ld_dst = new Operand(ld_se);
    // cout<<"ld_dst:"<<ld_dst->toStr()<<endl;
    Operand* dst = new Operand(ld_se);
    //f=true 说明end_bb为空
    //直接把ret_bb的blocknum改掉
    
    if(!isvoid){
        if(f){
            //cout<<"ld_dst:"<<ld_dst->toStr()<<endl;
            // func->ret_bb=new BasicBlock(func);
            // cout<<"**********ret_bb:"<<func->getRet()->getNo()<<endl;
            // cout<<"**********no:"<<no<<endl;
            func->ret_bb->setNo(no);//必须要setNo，因为这条指令是和ReturnStmt里的UncondBr耦合的
            LoadInstruction* loca=new LoadInstruction(ld_dst, ret_dst, func->getRet());
            RetInstruction* ret=new RetInstruction(dst,func->getRet());  
        }
        else{
            //cout<<"ld_dst:"<<ld_dst->toStr()<<endl;
            //end_bb不为空
            //直接把两条instruction（load&ret）加在end_bb块后面
            //UncondBrInstruction* toret = new UncondBrInstruction(func->ret_bb,bf);
            new UncondBrInstruction(func->ret_bb,bf);
            new LoadInstruction(ld_dst, ret_dst, func->getRet());
            new RetInstruction(dst,func->getRet());  
        }
    }
    else{
        BasicBlock* end=*(func->end()-1);
        if(end->getNo()==func->getRet()->getNo()){
            new RetInstruction(nullptr,func->getEntry());  
        }
        //else{
            if(f){
                func->ret_bb->setNo(no);
                RetInstruction* ret=new RetInstruction(nullptr,func->getRet());  
            }
            else{
                new UncondBrInstruction(func->ret_bb,bf);
                new RetInstruction(nullptr,func->getRet());  
            }
        //}
    }
    //cout<<"defEnd~!"<<endl;
    // loca->output();
    // ret->output();
    // ret_bb->output();   
}

void BinaryExpr::genCode()
{
    //cout<<"BinaryExpr~!"<<endl;
    BasicBlock *bb = builder->getInsertBB();
    //cout<<"bb_num:"<<bb->getNo()<<endl;
    Function *func = bb->getParent();
    if (op == AND)
    {
        //cout<<"AND~!"<<endl;
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();//expr1的代码在bb中

        //一定要重新getinsetbb!!因为expr1很可能调用了其他东西改了bb
        BasicBlock *now_bb = builder->getInsertBB();
        
        Instruction * inst;
        //生成bool型的判断dst
        if(expr1->getOperand()->getType()->toStr()=="i32"||expr1->getSymPtr()->getType()->toStr()=="i32()"){
            Operand * temp_dst = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));        
            new CmpInstruction(CmpInstruction::NE,temp_dst,expr1->getOperand(),const_0,now_bb);
            inst = new CondBrInstruction(trueBB,nullptr,temp_dst,now_bb);//连接bb,trueBB
        }else{
            inst = new CondBrInstruction(trueBB,nullptr,expr1->getOperand(),now_bb);//连接bb,trueBB
        }
        //很重要  inst的falselist必须接到false_list里（ifstmt回填）
        expr1->falseList().push_back(inst);//加入list

        backPatch(expr1->trueList(), trueBB);//回填expr1->trueList()
        //and短路，如果expr1正确，才需跳到trueBB继续计算expr2，后续语句在trueBB块生成
        //如果错误后续语句就还在当前块生成
        
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();//expr1的代码在trueBB中
        if(expr2->getOperand()->getType()->toStr()=="i32"||expr2->getSymPtr()->getType()->toStr()=="i32()"){
            new CmpInstruction(CmpInstruction::NE,dst,expr2->getOperand(),const_0,builder->getInsertBB());//生成bool型的判断dst
        }else{
            // new BinaryInstruction(BinaryInstruction::SAME, dst, expr2->getOperand(), expr2->getOperand(), builder->getInsertBB());
            new CmpInstruction(CmpInstruction::NE, dst, expr2->getOperand(), const_0, builder->getInsertBB());
        }
        // cout<<expr1->getSymPtr()->toStr()<<":"<<expr1->getSymPtr()->getType()->toStr()<<endl;
        // cout<<expr2->getSymPtr()->toStr()<<":"<<expr2->getSymPtr()->getType()->toStr()<<endl;
        // cout<<dst->toStr()<<":"<<dst->getType()->toStr()<<endl;
        true_list = expr2->trueList();//expr2->trueList就是true_list
        false_list = merge(expr1->falseList(), expr2->falseList());//二者的falseList均为整个expr的false_list
    }
    else if(op == OR)
    {
        //cout<<"OR~!"<<endl;
        // Todo ok 与and类似，短路判断
        BasicBlock *falseBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();

        BasicBlock *now_bb = builder->getInsertBB();

        //cout<<"now_bb:"<<now_bb->getNo()<<endl;
        //cout<<"falseBB:"<<falseBB->getNo()<<endl;
       
        Instruction * inst;
        Operand * temp_dst = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));        
        if(expr1->getOperand()->getType()->toStr()=="i32"||expr1->getSymPtr()->getType()->toStr()=="i32()"){
            new CmpInstruction(CmpInstruction::NE,temp_dst,expr1->getOperand(),const_0,now_bb);
            inst = new CondBrInstruction(nullptr,falseBB,temp_dst,now_bb);//连接bb,falseBB
        }else{
            inst = new CondBrInstruction(nullptr,falseBB,expr1->getOperand(),now_bb);//连接bb,falseBB
        }
        expr1->trueList().push_back(inst);//加入list

        backPatch(expr1->falseList(), falseBB, false);
        builder->setInsertBB(falseBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        if(expr2->getOperand()->getType()->toStr()=="i32"||expr2->getSymPtr()->getType()->toStr()=="i32()"){
            new CmpInstruction(CmpInstruction::NE,dst,expr2->getOperand(),const_0,builder->getInsertBB());
        }else{
            //new BinaryInstruction(BinaryInstruction::SAME, dst, expr2->getOperand(), expr2->getOperand(), builder->getInsertBB());
            new CmpInstruction(CmpInstruction::NE, dst, expr2->getOperand(), const_0, builder->getInsertBB());
        }
        
        
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = expr2->falseList();
        //cout<<"end???"<<endl;
    }
    else if(op >= LESS && op <= MORE)
    {
        // Todo
        //cout<<"LESS_MORE~!"<<endl;
        expr1->genCode();
        expr2->genCode();
        Operand * temp_src1 = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
        Operand * temp_src2 = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        BasicBlock *now_bb=builder->getInsertBB();
        if(expr1->getOperand()->getType()->toStr()=="i1"){
            new TypefixInstruction(temp_src1, expr1->getOperand(), now_bb);
            src1=temp_src1;
        }
        if(expr2->getOperand()->getType()->toStr()=="i1"){
            new TypefixInstruction(temp_src2, expr2->getOperand(), now_bb);
            src2=temp_src2;
        }
        int opcode;
        switch (op)
        {
        case LESS:
            opcode = CmpInstruction::L;
            break;
        case MORE:
            opcode = CmpInstruction::G;
            break;
        case MORE_E:
            opcode = CmpInstruction::GE;
            break;
        case LESS_E:
            opcode = CmpInstruction::LE;
            break;
        case EQUAL:
            opcode = CmpInstruction::E;
            break;
        case NOT_EQUAL:
            opcode = CmpInstruction::NE;
            break;
        
        }
        now_bb = builder->getInsertBB();//重新getInsertBB!!
        new CmpInstruction(opcode, dst, src1, src2, now_bb);
    }
    else if(op >= ADD && op <= MOD)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        case MUL:
            opcode = BinaryInstruction::MUL;
            break;
        case DIV:
            opcode = BinaryInstruction::DIV;
            break;
        case MOD:
            opcode = BinaryInstruction::MOD;
            break;
        }
        BasicBlock *now_bb = builder->getInsertBB();//重新getInsertBB!!
        new BinaryInstruction(opcode, dst, src1, src2, now_bb);
    }
}

void Constant::genCode()
{
    //cout<<"Constant~!"<<endl;
    // we don't need to generate code.
}

// void CondNode::genCode(){
//     //todo
//     cout<<"CondNode~!"<<endl;
//     //if(!expr)printf("$$$$$$$$$$");
//     expr->genCode();
//     true_list = expr->trueList();
//     false_list = expr->falseList();
//     //BasicBlock *bb = builder->getInsertBB();
//     //printf("expr1->getOperand():%s\n",expr->getOperand()->toStr().c_str());
//     //new CmpInstruction(CmpInstruction::E,dst,expr->getOperand(),nullptr,bb);
// }
void Id::genCode()
{
    //cout<<"Id~!"<<endl;
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    //cout<<"addr:"<<addr->toStr()<<endl;
    //cout<<"dst:"<<dst->toStr()<<endl;
    new LoadInstruction(dst, addr, bb);
}

void ArrayItem::genCode()
{
    cout<<"ArrayItem~!"<<endl;
    BasicBlock *bb = builder->getInsertBB();
    
    if(!offsets.empty()){
        for(auto & offset : offsets){
            // cout<<offset->getOperand()->toStr()<<endl;
            offset->genCode();
        }
    }
    Operand *addr = (dynamic_cast<IdentifierSymbolEntry*>(symbolEntry))->getAddr();
    cout<<"symbolEntry:"<<symbolEntry->toStr()<<endl;
    vector<int>dims=((ArrayType*)(symbolEntry->getType()))->get_dims();
    cout<<"dims:";
    for(auto& dim:dims){
        cout<<dim<<", ";
    }
    cout<<endl;
    if(dims[0]==0){//说明是参数
        cout<<"empty!"<<endl;
        bb = builder->getInsertBB();

        Type* array_type = (dynamic_cast<IdentifierSymbolEntry*>(symbolEntry))->getType();

        SymbolEntry *tmp_se = new TemporarySymbolEntry(array_type, SymbolTable::getLabel());
        Operand* temp_addr=new Operand(tmp_se);
        cout<<"offsets_size:"<<offsets.size()<<endl;

        Operand* offset_addr;
        if(offsets.empty()){
            cout<<"empty()"<<endl;
            offset_addr=const_0;

            new LoadInstruction(temp_addr, addr, bb);
            heads.push_back(temp_addr);
            // new ArrayItemFetchInstruction(array_type, heads[0], temp_addr, offset_addr, bb, true);
            // new LoadInstruction(dst, heads[0], bb);
        }
        else{
            cout<<"not empty()"<<endl;
            new LoadInstruction(temp_addr, addr, bb);
            dims.erase(dims.begin());
            Type* itype=((ArrayType*)array_type)->gettype();
            offset_addr=offsets[0]->getOperand();
            
            if(dims.empty()){
                heads.push_back(new Operand(new TemporarySymbolEntry(new PointerType(itype), SymbolTable::getLabel())));
                new ArrayItemFetchInstruction(itype, heads[0], temp_addr, offset_addr, bb, true);
                new LoadInstruction(dst, heads.back(), bb);
                return;
            }

            array_type=new ArrayType(itype, dims);
            
            heads.push_back(new Operand(new TemporarySymbolEntry(new PointerType(array_type), SymbolTable::getLabel())));
            cout<<array_type->toStr()<<endl;
            new ArrayItemFetchInstruction(array_type, heads[0], temp_addr, offset_addr, bb, true);
            
            int i=1;
            vector<ExprNode*> offsets_copy=offsets;
            offsets_copy.erase(offsets_copy.begin());
            if(!offsets_copy.empty()){
                for(auto& offset:offsets_copy){
                    offset_addr=offset->getOperand();  
                    Type* type;
                    dims.erase(dims.begin()); 
                    if(!dims.empty()){                    
                        type=new ArrayType(itype, dims);
                    }
                    else{
                        type=itype;
                    }
                    heads.push_back(new Operand(new TemporarySymbolEntry(new PointerType(type), SymbolTable::getLabel())));
                    new ArrayItemFetchInstruction(array_type, heads[i], heads[i-1], offset_addr, bb);
                    i++;
                    if(dims.empty()){
                        break;
                    }
                }
            }
            new LoadInstruction(dst, heads.back(), bb);
        }
    }
    else{
        Type* itype=((ArrayType*)(symbolEntry->getType()))->gettype();
        //vector<int> dims=((ArrayType*)(symbolEntry->getType()))->get_dims();
        // Operand* temp1 = new Operand(new TemporarySymbolEntry(new PointerType(((ArrayType*)(symbolEntry->getType()))->gettype()), SymbolTable::getLabel()));
        // new LoadInstruction(temp1, addr, bb);
        int i=0;
        heads.clear();
        if(offsets.empty()){
            
            Type *array_type=new ArrayType(itype, dims);
            cout<<array_type->toStr()<<endl;
            
            // dims.erase(dims.begin());
            // Type *sub_type;           
            // sub_type=((ArrayType*)(symbolEntry->getType()))->gettype();
            Type* itype=((ArrayType*)(array_type))->gettype();
            Type* type;
            if(dims.size()>1){
                dims.erase(dims.begin());
                type=new ArrayType(itype, dims);
            }
            else{
                type=itype;
            }
            
            Type* ptype = new PointerType(type);//数组元素的类型
            SymbolEntry *tmp_se = new TemporarySymbolEntry(ptype, SymbolTable::getLabel());
            Operand* temp_addr=new Operand(tmp_se);
            heads.push_back(temp_addr);

            new ArrayItemFetchInstruction(array_type, temp_addr, addr, const_0, bb);
            //new LoadInstruction(dst, heads[0], bb);
            return;
        }
        cout<<"offsets size:"<<offsets.size()<<endl;
        for(auto & offset : offsets){
            cout<<"???"<<endl;
            Operand *offset_addr = offset->getOperand();
            // Type *array_type = ((ArrayType*)(symbolEntry->getType()))->gettype();
            Type *array_type=new ArrayType(itype, dims);
            // cout<<array_type->toStr()<<endl;
            dims.erase(dims.begin());
            Type *sub_type;
            if(dims.empty()){
                sub_type=((ArrayType*)(symbolEntry->getType()))->gettype();
            }
            else{
                sub_type=new ArrayType(itype, dims);
            }
            Type* type = new PointerType(sub_type);//数组元素的类型
            SymbolEntry *tmp_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
            Operand* temp_addr=new Operand(tmp_se);

            if(f)offset_addr=const_0;

            new ArrayItemFetchInstruction(array_type, temp_addr, addr, offset_addr, bb);
            addr=temp_addr;
            heads.push_back(temp_addr);
            
            if(dims.empty())
                break;
            i++;
        }
        cout<<"??"<<endl;
        new LoadInstruction(dst, heads.back(), bb);
    }
}

void IfStmt::genCode()
{
    //cout<<"ifstmt~!"<<endl;
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    //条件判断block
    cond->genCode();//生成条件判断语句的中间代码
    backPatch(cond->trueList(), then_bb);//回填trueList的后续block为then_bb
    backPatch(cond->falseList(), end_bb,false);//回填falseList的后续block为end_bb
    BasicBlock * bb = builder->getInsertBB();
    //cout<<cond->getOperand()->toStr()<<":"<<cond->getOperand()->getType()->toStr()<<endl;
    if(cond->getOperand()->getType()->toStr()=="i32"||cond->getSymPtr()->getType()->toStr()=="i32()"){        
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        new CmpInstruction(CmpInstruction::NE,temp,cond->getOperand(),const_0,bb);//int转bool
        new CondBrInstruction(then_bb,end_bb,temp,bb);
    }
    else
        new CondBrInstruction(then_bb,end_bb,cond->getOperand(),bb);

    //then block
    builder->setInsertBB(then_bb);
    thenStmt->genCode();


    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);//在thenblock最后加上无条件跳转语句
    //then_bb->output();
    
    //后续block为end_bb
    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    //cout<<"ifelsestmt~!"<<endl;
    // Todo ok
    Function *func;
    BasicBlock *then_bb, *else_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    else_bb = new BasicBlock(func);

    //条件判断block
    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), else_bb,false);
    BasicBlock * bb = builder->getInsertBB();
    //判断cond是否为布尔类型
    if(cond->getOperand()->getType()->toStr()=="i32"||cond->getOperand()->getType()->toStr()=="i32()"){
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        new CmpInstruction(CmpInstruction::NE,temp,cond->getOperand(),const_0,bb);//int转bool
        new CondBrInstruction(then_bb,else_bb,temp,bb);
    }
    else
        new CondBrInstruction(then_bb,else_bb,cond->getOperand(),bb);

    //then block
    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    //else block
    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, else_bb);

    //后续block为end_bb
    builder->setInsertBB(end_bb);
}


void CompoundStmt::genCode()
{
    //cout<<"CompoundStmt~!"<<endl;
    // Todo ok
    stmt->genCode();
}

void SeqNode::genCode()
{
    //cout<<"seqnode~!"<<endl;
    // Todo ok
    stmt1->genCode();
    stmt2->genCode();
}

void DeclStmt::genCode()
{
    // cout<<"DeclStmt~!"<<endl;
    //TODO ok
    map<Id*, ExprNode*>::iterator iter;
    for(iter = idlist.begin();iter!=idlist.end();iter++){
        IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>((iter->first)->getSymPtr());
        if(se->isGlobal())//scope==GLOBAL（就是0）
        {
            Operand *addr;
            SymbolEntry *addr_se;
            addr_se = new IdentifierSymbolEntry(*se);
            addr_se->setType(new PointerType(se->getType()));
            addr = new Operand(addr_se);
            se->setAddr(addr);

            std::string dst, type;
            dst = addr->toStr();
            type = se->getType()->toStr();

            BasicBlock* bb=builder->getInsertBB();
            
            //new GlobalInstruction(addr, se, bb); 
            if(iter->second){
                BasicBlock *bb = builder->getInsertBB();
                iter->second->genCode();
                Operand *src = iter->second->getOperand();
                new StoreInstruction(addr, src, bb);
                string dst1 = addr->toStr();
                string src1 = src->toStr();
                string dst_type1 = addr->getType()->toStr();
                string src_type1 = src->getType()->toStr();
                //printf("%s = global %s %s, align 4\n", dst.c_str(), type.c_str(),src1.c_str());
                //new GlobalInstruction(addr,se);
                fprintf(yyout, "%s = global %s %s, align 4\n", dst.c_str(), type.c_str(),src1.c_str());
            }
            else{
                fprintf(yyout, "%s = global %s 0, align 4\n", dst.c_str(), type.c_str());
            }

        }
        else if(se->isLocal())
        {
            //根据符号表项se分配地址（operand以地址方式存在）
            Function *func = builder->getInsertBB()->getParent();
            BasicBlock *entry = func->getEntry();
            Instruction *alloca;
            Operand *addr;
            SymbolEntry *addr_se;
            Type *type;
            type = new PointerType(se->getType());
            addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
            //addr = iter->first->getOperand();//new Operand(addr_se);
            addr = new Operand(addr_se);
            // cout<<"addr:"<<addr->getType()->toStr()<<endl;
            // set the addr operand in symbol entry so that we can use it in subsequent code generation.
            alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
            //如果声明的同时赋值，需要跟Store指令
            if(iter->second){
                BasicBlock *bb = builder->getInsertBB();
                iter->second->genCode();
                Operand *src = iter->second->getOperand();
                new StoreInstruction(addr, src, bb);
                //printf("19 ");
            }
            cout<<"setAddr~~ "<<se->toStr()<<endl;
            se->setAddr(addr);  
            entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block.
        }
    }
    map<Id*, vector<ExprNode*>>::iterator array_iter;
    for(array_iter = arraylist.begin();array_iter!=arraylist.end();array_iter++){
        IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>((array_iter->first)->getSymPtr());
        if(se->isGlobal()){
            cout<<"----Global!!"<<endl;
            cout<<se->toStr()<<endl;
            Operand *addr;
            SymbolEntry *addr_se;
            addr_se = new IdentifierSymbolEntry(*se);
            addr_se->setType(new PointerType(se->getType()));
            addr = new Operand(addr_se);
            se->setAddr(addr);

            std::string dst, type;
            dst = addr->toStr();
            type = se->getType()->toStr();

            BasicBlock* bb=builder->getInsertBB();

            bool f=false;
            if(!array_iter->second.empty()){
                for(auto& sc:array_iter->second){
                    if(sc){
                        f=true;
                        break;
                    }
                }
            }

            if(f&&!array_iter->second.empty()){
                vector<ExprNode*> explist=array_iter->second;
                
                BasicBlock *bb = builder->getInsertBB();

                std::ostringstream buffer;
                deque<string> q;
                //buffer<<dst<<" = global "<<type;
                vector<int> dc;//计数
                vector<int> dims=((ArrayType*)(se->getType()))->get_dims();
                vector<int> dims_copy;
                int total=1;
                //cout<<"dims: ";
                for(auto & dim : dims){
                    dc.push_back(0);
                    total*=dim;
                    //cout<<dim<<", ";
                }
                //cout<<endl;
                int maxsize=dims.size();
                Type* itype=((ArrayType*)(se->getType()))->gettype();
                Type *sub_type=((ArrayType*)(se->getType()))->gettype();
                Type *init_type=sub_type;
                int count=0;
                //buffer<<"[";
                bool runFlag=true;
                while(runFlag){
                    cout<<"count:"<<count<<endl;
                    cout<<"dc.back():"<<dc.back()<<endl;
                    if(dc.back()==dims.back()){
                        cout<<"----enter if"<<endl;
                        int i=dc.size()-1;
                        //进位
                        while(i>=0){
                            dc[i]=0;
                            //if(i>0){
                                if(i>0&&dc[i-1]+1==dims[i-1]){
                                    //未找到进位
                                    cout<<"11"<<endl;
                                    i--;
                                    continue;
                                }
                                else{
                                    cout<<"22"<<endl;
                                    //找到进位
                                    //q.pop_back();//弹出最后的逗号
                                    for(int k=dc.size()-1;k>=i;k--){
                                        buffer<<"["<<dims[k]<<" x "<<sub_type->toStr()<<"] ";
                                        //dims_copy.push_back(dims[k]);
                                        dims_copy=dims;
                                        while(dims_copy.size()!=dc.size()-k){
                                            dims_copy.erase(dims_copy.begin());
                                        }
                                        sub_type=new ArrayType(itype, dims_copy);
                                        string temp_str=buffer.str();
                                        buffer.str("");
                                        deque<string> temp_q;
                                        for(int x=0;x<dims[k];x++){
                                            temp_q.push_back(q.back());
                                            q.pop_back();
                                        }
                                        temp_str+="[";
                                        for(int x=0;x<dims[k];x++){
                                            temp_str+=temp_q.back();
                                            temp_q.pop_back();
                                            if(x<dims[k]-1)temp_str+=", ";
                                        }
                                        temp_str+="]";
                                        q.push_back(temp_str);
                                    }
                                    if(i>0){
                                        dc[i-1]++;
                                    }
                                    else{
                                        runFlag=false;
                                    }
                                    break;
                                }
                            //}
                            i--;
                        }
                    }
                    else{
                        cout<<"----enter else"<<endl;
                        int val=0;
                        // cout<<"explist[count]:"<<(explist.size())<<endl;
                        if(explist[count]){
                            //val=((ConstantSymbolEntry*)(explist[count]->getSymPtr()))->getValue();
                            val=(explist[count]->getSymPtr())->get_value();
                        }              
                        //buffer.clear();
                        sub_type=init_type;
                        dims_copy.clear();
                        buffer<<init_type->toStr()<<" "<<val;
                        q.push_back(buffer.str());
                        //q.push_back(",");//先不加逗号
                        buffer.str("");
                        dc.back()++;
                        count++;
                    }                   
                    // for(auto & str:q){
                    //     cout<<str<<"|";
                    // }
                    // cout<<endl;
                    //maxsize--;
                }
                buffer.str("");
                for(auto & str:q){
                    //cout<<str<<"|";
                    buffer<<str;
                    if(str!=q.back())buffer<<", ";
                }
                //cout<<endl;
                fprintf(yyout, "%s = global %s, align 4\n", dst.c_str(), buffer.str().c_str());
                //new GlobalInstruction(addr,se);
                //fprintf(yyout, "%s", buffer.str().c_str());
            }
            else{
                fprintf(yyout, "%s = global %s zeroinitializer, align 4\n", dst.c_str(), type.c_str());
            }
        }
        else{
            //根据符号表项se分配地址（operand以地址方式存在）
            Function *func = builder->getInsertBB()->getParent();
            BasicBlock *entry = func->getEntry();
            Instruction *alloca;
            Operand *addr;
            Operand *src;
            SymbolEntry *addr_se;
            Type *type;
            type = new PointerType(se->getType());
            addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
            //addr = iter->first->getOperand();//new Operand(addr_se);
            addr = new Operand(addr_se);
            // cout<<"addr:"<<addr->getType()->toStr()<<endl;
            cout<<"se:"<<se->getType()->toStr()<<endl;
                                                    // set the addr operand in symbol entry so that we can use it in subsequent code generation.
            alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
            //如果声明的同时赋值，需要跟Store指令
            vector<int> dc;//计数
            vector<int> dims=((ArrayType*)(se->getType()))->get_dims();
            for(auto & dim : dims){
                dc.push_back(0);
            }
            int maxsize=dc.size();
            if(!array_iter->second.empty()){
                // cout<<"--------------explist: ";
                // int v=0;
                // for(auto & exp:array_iter->second){
                //     if(exp)v=exp->getSymPtr()->get_value();
                //     cout<<v<<", ";
                //     v=0;
                // }
                // cout<<endl;
                BasicBlock* bb=builder->getInsertBB();
                cout<<"explist:"<<array_iter->second.size();
                for(auto & exp : array_iter->second){
                    vector<int> dims_copy=dims;
                    Type* itype=((ArrayType*)(se->getType()))->gettype();
                    Operand* addr_copy=addr;
                    //int i=0;
                    for(auto &off:dc){
                        Operand *offset_addr = new Operand(new ConstantSymbolEntry(TypeSystem::intType, off));
                        // Type *array_type = ((ArrayType*)(symbolEntry->getType()))->gettype();
                        Type *array_type=new ArrayType(itype, dims_copy);
                        cout<<array_type->toStr()<<endl;

                        dims_copy.erase(dims_copy.begin());
                        Type *sub_type;
                        if(dims_copy.empty()){
                            sub_type=((ArrayType*)(se->getType()))->gettype();
                        }
                        else{
                            sub_type=new ArrayType(itype, dims_copy);
                        }
                        Type* type = new PointerType(sub_type);//数组元素的类型
                        SymbolEntry *tmp_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
                        Operand* temp_addr=new Operand(tmp_se);
                        
                        new ArrayItemFetchInstruction(array_type, temp_addr, addr_copy, offset_addr, bb);
                        addr_copy=temp_addr;
                        if(dims_copy.empty())
                            break;
                        //i++;
                    }

                    if(exp){
                        //不为空
                        cout<<"! nullptr"<<endl;
                        exp->genCode();
                        bb=builder->getInsertBB();
                        src=exp->getOperand();
                    }
                    else{
                        //为空，赋初值0
                        cout<<"nullptr"<<endl;
                        src=const_0;
                    }
                    bb=builder->getInsertBB();
                    new StoreInstruction(addr_copy, src, bb);

                    //dc.back()++;
                    if(dc.back()+1==dims.back()){
                        int i=dc.size()-1;
                        //进位
                        while(i>=0){
                            dc[i]=0;
                            if(i>0){
                                if(dc[i-1]+1==dims[i-1]){
                                    i--;
                                    continue;
                                }
                                else{
                                    dc[i-1]++;
                                    break;
                                }
                            }
                            i--;
                        }
                    }
                    else
                        dc.back()++;
                    // cout<<"dc: ";
                    // for(auto &d : dc){
                    //     cout<<d<<", ";
                    // }
                    // cout<<endl;
                    // if(dc[0]+1==dims[0]){
                    //     break;
                    // }
                    
                    
                }
                // new LoadInstruction(dst, heads[i], bb);
                
                //printf("19 ");
            }
            cout<<"setAddr~~ "<<se->toStr()<<endl;
            se->setAddr(addr);  
            entry->insertFront(alloca);  
        }  
    }
}

void ReturnStmt::genCode()
{
    //cout<<"ReturnStmt~!"<<endl;
    // Todo ok
    
    BasicBlock *bb = builder->getInsertBB();
    Function* func=bb->getParent();
    if(retValue){
        retValue->genCode();
        SymbolEntry *se = retValue->getSymPtr();
        ret_ope=retValue->getOperand();
        bb = builder->getInsertBB();
        //cout<<"ret_dst:"<<ret_dst->toStr()<<endl;
        //cout<<"ret_ope:"<<ret_ope->toStr()<<endl;
        new StoreInstruction(ret_dst,ret_ope, bb);//存储形参
        new UncondBrInstruction(func->ret_bb, bb);
    }
    else{
        new UncondBrInstruction(func->ret_bb, bb);
    }
}
void sufSingleExpr::genCode()
{
    // Todo ok
    expr->genCode();

    BasicBlock *bb = builder->getInsertBB();
    Operand *const_1 = new Operand(new ConstantSymbolEntry(dst->getType(), 1));
    Operand *temp = new Operand(new TemporarySymbolEntry(dst->getType(), SymbolTable::getLabel()));
    int opcode;
    switch (op)
    {
    case AADD:
        opcode = BinaryInstruction::ADD;
        break;
    case SSUB:
        opcode = BinaryInstruction::SUB;
        break;
    }
    new BinaryInstruction(opcode, temp, dst, const_1, bb);
    Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(expr->getSymPtr())->getAddr();
    new StoreInstruction(addr, temp, bb);

    true_list = expr->trueList();
    false_list = expr->falseList();
}
void preSingleExpr::genCode()
{
    // Todo ok
    expr->genCode();

    //常数1和常数0

    BasicBlock *bb = builder->getInsertBB();
    Operand *temp = new Operand(new TemporarySymbolEntry(dst->getType(), SymbolTable::getLabel()));
    int opcode;
    
    if(op>=AADD&&op<=SSUB){
        switch (op)
        {
        case AADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SSUB:
            opcode = BinaryInstruction::SUB;
            break;
        default:
            break;
        }
        Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(expr->getSymPtr())->getAddr();
        new LoadInstruction(dst, addr, bb);
        new BinaryInstruction(opcode, temp, dst, const_1, bb);
        new StoreInstruction(addr, temp, bb);
    }
    else if(op==SUB){
        Operand *temp1 = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
        //cout<<expr->getSymPtr()->getType()->toStr()<<endl;
        if(expr->getOperand()->getType()->toStr()=="i1"){
            new TypefixInstruction(temp1, expr->getOperand(), bb);
            new BinaryInstruction(BinaryInstruction::SUB, dst, const_0, temp1, bb);
        }
        else{
            new BinaryInstruction(BinaryInstruction::SUB, dst, const_0, expr->getOperand(), bb);
        }
        //else{
        //     new TypefixInstruction(temp1, expr->getOperand(), bb);
        //     Operand *temp2 = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
        //     new BinaryInstruction(BinaryInstruction::SUB, temp2, const_0, temp1, bb);
        //     new CmpInstruction(CmpInstruction::NE,dst,temp2,const_0,bb);//int转bool
        // }
    }
    else if(op==NOT){
        //cout<<"NOT~!"<<endl;
        opcode=BinaryInstruction::NOT;
        
        //临时变量没有地址！不用load/store直接在寄存器上运算就行
        if(expr->getOperand()->getType()->toStr()=="i32"){
            //Operand *addr = dynamic_cast<IdentifierSymbolEntry *>(expr->getSymPtr())->getAddr();
            Operand *temp1 = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
            Operand *temp2 = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
            //new LoadInstruction(temp1, addr, bb);
            new CmpInstruction(CmpInstruction::NE,temp1,expr->getOperand(),const_0,bb);//int转bool
            //new TypefixInstruction(temp2, temp1, bb);
            new BinaryInstruction(opcode, dst, temp1, temp1, bb);
            //Operand *temp3 = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
            //
            //new StoreInstruction(addr, temp2, bb);
        }
        else{
            new BinaryInstruction(opcode, dst, expr->getOperand(), expr->getOperand(), bb);
        }
    }

    true_list = expr->trueList();
    false_list = expr->falseList();
    
    
}
void FunctionCall::genCode()
{
    // Todo ok
    cout<<"FunctionCall~!"<<endl;
    Function *func= builder->getInsertBB()->getParent();
    BasicBlock *nowb = builder->getInsertBB();
    vector<Operand*> vo;
    std::string name;

    std::vector<Type*> types = ((FunctionType*)(se->getType()))->paramsType;

    if(!params.empty()){
        for(unsigned int i = 0;i < params.size(); i++)
        {
            cout<<"hi1"<<endl;
            params[i]->genCode();
            cout<<"hi2"<<endl;
            Operand *src=params[i]->getOperand();
            if(params[i]->isArray()){
                cout<<"haha------"<<endl;
                if(((ArrayItem*)(params[i]))->getf())
                    src=((ArrayItem*)(params[i]))->heads[0];
            }
            vo.push_back(src);
        }
    }

    new CallInstruction(symbolEntry,dst,vo,nowb);
    Operand *dsts=dst;

    if (((IdentifierSymbolEntry*)se)->isSysy()) {
        vector<SymbolEntry*> v=func->getParent()->sysy_list;
        if(std::find(v.begin(), v.end(), se) == v.end()){//去重
            func->getParent()->sysy_list.push_back(se);
        }
    }
}
void EmptyStmt::genCode()
{
    // Todo ok
}
void BreakStmt::genCode()
{
    //cout<<"BreakStmt~!"<<endl;
    BasicBlock* bb=builder->getInsertBB();
    BasicBlock* end_bb=((WhileStmt*)parent)->get_end_bb();
    new UncondBrInstruction(end_bb, bb);
}
void ContinueStmt::genCode()
{
    //cout<<"ContinueStmt~!"<<endl;
    BasicBlock* bb=builder->getInsertBB();
    BasicBlock* cond_bb=((WhileStmt*)parent)->get_cond_bb();
    new UncondBrInstruction(cond_bb, bb);
}
void ExprStmt::genCode()
{
    // Todo ok
    exp->genCode();
}
void WhileStmt::genCode()
{
    // cout<<"WhileStmt~!"<<endl;
    // Todo ok
    // 和ifstmt有区别：cond必须为一个独立的basicblock（cond实际上无条件接在end_bb后面）
    Function *func;
    BasicBlock *then_bb, *end_bb, *cond_bb;

    func = builder->getInsertBB()->getParent();
    //cout<<func->getSymPtr()->toStr()<<endl;
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    cond_bb = new BasicBlock(func);

    this->end_bb=end_bb;
    this->cond_bb=cond_bb;

    BasicBlock* bb = builder->getInsertBB();
    //cout<<"bb:"<<bb->getNo()<<endl;
    // cond无条件接在当前bb后
    
    new UncondBrInstruction(cond_bb, bb);
    builder->setInsertBB(cond_bb);

    //cond block 
    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    //end_bb只能有条件接在cond_bb后面
    backPatch(cond->falseList(), end_bb, false);
    cond_bb=builder->getInsertBB();
    //cout<<"cond_bb:"<<cond_bb->getNo()<<endl;
    cout<<cond->getOperand()->toStr();
    if(cond->getOperand()->getType()->toStr()=="i32"||cond->getOperand()->getType()->toStr()=="i32()"){
        Operand *temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
        new CmpInstruction(CmpInstruction::NE,temp,cond->getOperand(),const_0,cond_bb);//int转bool
        new CondBrInstruction(then_bb,end_bb,temp,cond_bb);
    }
    else
        new CondBrInstruction(then_bb,end_bb,cond->getOperand(),cond_bb);
    
    //then block
    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(this->cond_bb, then_bb);

    builder->setInsertBB(end_bb);
}
void AssignStmt::genCode()
{
    cout<<"AssignStmt~!"<<endl;

    //要检测lval的类型了！！
    expr->genCode();

    if(lval->isId()){
        BasicBlock *bb = builder->getInsertBB();        
        IdentifierSymbolEntry* se = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr());
        //cout<<"se:"<<se<<endl;
        Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
        Operand *src = expr->getOperand();
        /***
         * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
         * If you want to implement array, you have to caculate the address first and then store the result into it.
         */
        //cout<<"lval?"<<(lval->getOperand()->toStr())<<endl;
        //cout<<"expr?"<<(expr->getOperand()->toStr())<<endl;
        //cout<<"addr?"<<(addr->toStr())<<endl;
        //不能用lval->getOperand()了！！
        new StoreInstruction(addr, expr->getOperand(), bb);
    }
    else if(lval->isArray()){
        BasicBlock* bb=builder->getInsertBB();
        // cout<<lval->getSymPtr()->toStr()<<endl;
        // cout<<(((ArrayType*)(lval->getSymPtr()->getType()))->dims.empty())<<endl;
        // vector<int> dims=((ArrayType*)(lval->getSymPtr()->getType()))->get_dims();
        // SymbolEntry* se=lval->getSymPtr();
        // Operand *src;
        // Operand* addr=((IdentifierSymbolEntry*)se)->getAddr();
        // //vector<int> dc;//计数
        // if(dims.empty()){
        //     bb = builder->getInsertBB();

        //     Type* array_type = (dynamic_cast<IdentifierSymbolEntry*>(se))->getType();

        //     SymbolEntry *tmp_se = new TemporarySymbolEntry(array_type, SymbolTable::getLabel());
        //     Operand* temp_addr=new Operand(tmp_se);

        //     vector<ExprNode*> offsets=((ArrayItem*)(lval))->get_offsets();
        //     Operand* offset_addr=offsets[0]->getOperand();
        //     offsets[0]->genCode();
        //     bb=builder->getInsertBB();

        //     Operand* expr_addr=expr->getOperand();

        //     new LoadInstruction(temp_addr, addr, bb);
        //     Operand* newhead=new Operand(new TemporarySymbolEntry(new PointerType(((ArrayType*)(array_type))->gettype()), SymbolTable::getLabel()));
        //     ((ArrayItem*)(lval))->heads.push_back(newhead);
        //     new ArrayItemFetchInstruction(array_type, newhead, temp_addr, offset_addr, bb, true);
        //     new StoreInstruction(newhead, expr_addr, bb);
        // }
        // else{
        //     // for(auto & dim : dims){
        //     //     dc.push_back(0);
        //     // }
        //     vector<ExprNode*> offsets=((ArrayItem*)(lval))->get_offsets();
        //     Operand* temp_addr;
        //     for(auto & exp : offsets){
        //         //cout<<"-------dc:"<<dc.back()<<endl;
        //         vector<int> dims_copy=dims;
        //         Type* itype=((ArrayType*)(se->getType()))->gettype();
        //         Operand* addr_copy=addr;
        //         //int i=0;
        //         exp->genCode();
        //         bb=builder->getInsertBB();
        //         //for(auto &off:dc){
        //         //Operand *offset_addr = new Operand(new ConstantSymbolEntry(TypeSystem::intType, off));
        //         Operand *offset_addr=exp->getOperand();
        //         // Type *array_type = ((ArrayType*)(symbolEntry->getType()))->gettype();
        //         Type *array_type=new ArrayType(itype, dims_copy);
        //         cout<<array_type->toStr()<<endl;

        //         dims_copy.erase(dims_copy.begin());
        //         Type *sub_type;
        //         if(dims_copy.empty()){
        //             sub_type=((ArrayType*)(se->getType()))->gettype();
        //         }
        //         else{
        //             sub_type=new ArrayType(itype, dims_copy);
        //         }
        //         Type* type = new PointerType(sub_type);//数组元素的类型
        //         SymbolEntry *tmp_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        //         temp_addr=new Operand(tmp_se);

        //         // if(exp==offsets.back()){
        //         //     temp_addr=lval->getOperand();
        //         // }
                
        //         new ArrayItemFetchInstruction(array_type, temp_addr, addr_copy, offset_addr, bb);
        //         addr_copy=temp_addr;
        //         if(dims_copy.empty())
        //             break;
        //             //i++;
        //         //}

        //         // if(exp){
        //         //     //不为空
        //         //     cout<<"! nullptr"<<endl;
        //         //     exp->genCode();
        //         //     bb=builder->getInsertBB();
        //         //     src=exp->getOperand();
        //         // }
        //         // else{
        //         //     //为空，赋初值0
        //         //     cout<<"nullptr"<<endl;
        //         //     src=const_0;
        //         // }
                
        //         // //dc.back()++;                
        //         // if(dc.back()+1==dims.back()){
        //         //     int i=dc.size()-1;
        //         //     //进位
        //         //     while(i>=0){
        //         //         dc[i]=0;
        //         //         if(i>0){
        //         //             if(dc[i-1]+1==dims[i-1]){
        //         //                 i--;
        //         //                 continue;
        //         //             }
        //         //             else{
        //         //                 dc[i-1]++;
        //         //                 break;
        //         //             }
        //         //         }
        //         //         i--;
        //         //     }
        //         // }
        //         // else{
        //         //     cout<<"++??"<<endl;
        //         //     dc.back()++; 
        //         // }
        //     }
        //     bb=builder->getInsertBB();
        //     src=expr->getOperand();
            
            //new StoreInstruction(temp_addr, src, bb);

        //}
        lval->genCode();
        bb=builder->getInsertBB();
        Operand* dst=((ArrayItem*)lval)->heads.back();
        new StoreInstruction(dst, expr->getOperand(), bb);
    }
}
void EmptyStmt::typeCheck()
{
    // Todo
}
void BreakStmt::typeCheck()
{
    // Todo
}
void ContinueStmt::typeCheck()
{
    // Todo
}
void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    // Todo
}
// 


void BinaryExpr::typeCheck()
{
    // Todo
}

void Constant::typeCheck()
{
    // Todo
}
void ExprStmt::typeCheck()
{
    // Todo
}
void WhileStmt::typeCheck()
{
    // Todo
}
void Id::typeCheck()
{
    // Todo
}
void ArrayItem::typeCheck()
{
    // Todo
}

void IfStmt::typeCheck()
{
    // Todo
}

void IfElseStmt::typeCheck()
{
    // Todo
}

void CompoundStmt::typeCheck()
{
    // Todo
}

void SeqNode::typeCheck()
{
    // Todo
}

void DeclStmt::typeCheck()
{
    // Todo
}

void ReturnStmt::typeCheck()
{
    // Todo
}

void AssignStmt::typeCheck()
{
    // Todo
}
void FunctionCall::typeCheck()
{
    // Todo
}
void sufSingleExpr::typeCheck()
{
    // Todo
}
void preSingleExpr::typeCheck()
{
    // Todo
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case MORE:
            op_str = "more";
            break;
        case EQUAL:
            op_str = "equal";
            break;
        case MORE_E:
            op_str = "more_than_or_equal";
            break;
        case LESS_E:
            op_str = "less_than_or_equal";
            break;
        case NOT_EQUAL:
            op_str = "not_equal";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void preSingleExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case NOT:
            op_str = "not";
            break;
        case AADD:
            op_str = "prefix_self_add";
            break;
        case SSUB:
            op_str = "prefix_self_sub";
            break;
    }
    fprintf(yyout, "%*cprefix_SingleExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

void sufSingleExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case AADD:
            op_str = "suffix_self_add";
            break;
        case SSUB:
            op_str = "suffix_self_sub";
            break;
    }
    fprintf(yyout, "%*csuffix_SingleExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}


void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    // bool isconst = symbolEntry->getType()->is_const();
    // scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    // fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\tis_const:%d\n", level, ' ',
    //         name.c_str(), scope, type.c_str(), isconst);
}

void ArrayItem::output(int level)
{
    cout<<"ArrayItem::output"<<endl;
    // std::string name, type;
    // int scope;
    // name = symbolEntry->toStr();
    // type = symbolEntry->getType()->toStr();
    // bool isconst = symbolEntry->getType()->is_const();
    // scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    // fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\tis_const:%d\n", level, ' ',
    //         name.c_str(), scope, type.c_str(), isconst);
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    std::map<Id*, ExprNode*>::iterator it=idlist.begin();
    while(it!=idlist.end()){
        it->first->output(level + 4);
        if(it->second!=nullptr){
            it->second->output(level+4);
        }
        it++;
    }
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}


void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if(!retValue){
        retValue->output(level + 4);
    }
}

void ExprStmt::output(int level)
{
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
    if(exp){
        exp->output(level + 4);
    }
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    stmt->output(level + 4);
}

void FunctionCall::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionCall function name: %s, type: %s, params_num: %d\n", level, ' ', 
            name.c_str(), type.c_str(), int(params.size()));
    //vector<SymbolEntry*>::iterator it=params.begin();
    if(params.empty()){
        return;
    }
}

void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}
void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}
void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}
