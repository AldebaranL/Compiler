#include "Instruction.h"
#include "BasicBlock.h"
#include <iostream>
#include <vector>
#include "Function.h"
#include "Type.h"
using namespace std;

extern FILE* yyout;

Instruction::Instruction(unsigned instType, BasicBlock *insert_bb)
{
    prev = next = this;
    opcode = -1;
    this->instType = instType;
    if (insert_bb != nullptr)
    {
        insert_bb->insertBack(this);
        parent = insert_bb;
    }
}

Instruction::~Instruction()
{
    parent->remove(this);
}

BasicBlock *Instruction::getParent()
{
    return parent;
}

void Instruction::setParent(BasicBlock *bb)
{
    parent = bb;
}

void Instruction::setNext(Instruction *inst)
{
    next = inst;
}

void Instruction::setPrev(Instruction *inst)
{
    prev = inst;
}

Instruction *Instruction::getNext()
{
    return next;
}

Instruction *Instruction::getPrev()
{
    return prev;
}

BinaryInstruction::BinaryInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb) : Instruction(BINARY, insert_bb)
{
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

BinaryInstruction::~BinaryInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void BinaryInstruction::output() const
{
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[0]->getType()->toStr();
    switch (opcode)
    {
    case ADD:
        op = "add";
        break;
    case SUB:
        op = "sub";
        break;
    case MUL:
        op = "mul";
        break;
    case DIV:
        op = "sdiv";
        break;
    case MOD:
        op = "srem";
        break;
    case NOT:
        op = "xor";
        fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), "true");
        return;
        break;
    case SAME:
        op = "xor";
        fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), "false");
        return;
        break;
    default:
        break;
    }
    fprintf(yyout, "  %s = %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), s3.c_str());
}

CmpInstruction::CmpInstruction(unsigned opcode, Operand *dst, Operand *src1, Operand *src2, BasicBlock *insert_bb): Instruction(CMP, insert_bb){
    this->opcode = opcode;
    operands.push_back(dst);
    operands.push_back(src1);
    operands.push_back(src2);
    dst->setDef(this);
    src1->addUse(this);
    src2->addUse(this);
}

CmpInstruction::~CmpInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void CmpInstruction::output() const
{
    std::string s1, s2, s3, op, type;
    s1 = operands[0]->toStr();
    s2 = operands[1]->toStr();
    s3 = operands[2]->toStr();
    type = operands[1]->getType()->toStr();
    switch (opcode)
    {
    case E:
        op = "eq";
        break;
    case NE:
        op = "ne";
        break;
    case L:
        op = "slt";
        break;
    case LE:
        op = "sle";
        break;
    case G:
        op = "sgt";
        break;
    case GE:
        op = "sge";
        break;
    default:
        op = "";
        break;
    }

    fprintf(yyout, "  %s = icmp %s %s %s, %s\n", s1.c_str(), op.c_str(), type.c_str(), s2.c_str(), s3.c_str());
}

UncondBrInstruction::UncondBrInstruction(BasicBlock *to, BasicBlock *insert_bb) : Instruction(UNCOND, insert_bb)
{
    branch = to;
}

void UncondBrInstruction::output() const
{
    fprintf(yyout, "  br label %%B%d\n", branch->getNo());
}

void UncondBrInstruction::setBranch(BasicBlock *bb)
{
    branch = bb;
}

BasicBlock *UncondBrInstruction::getBranch()
{
    return branch;
}

CondBrInstruction::CondBrInstruction(BasicBlock*true_branch, BasicBlock*false_branch, Operand *cond, BasicBlock *insert_bb) : Instruction(COND, insert_bb){
    this->true_branch = true_branch;
    this->false_branch = false_branch;
    cond->addUse(this);
    operands.push_back(cond);
}

CondBrInstruction::~CondBrInstruction()
{
    operands[0]->removeUse(this);
}

void CondBrInstruction::output() const
{
    std::string cond, type;
    cond = operands[0]->toStr();
    type = operands[0]->getType()->toStr();
    int true_label = true_branch->getNo();
    int false_label = false_branch->getNo();
    fprintf(yyout, "  br %s %s, label %%B%d, label %%B%d\n", type.c_str(), cond.c_str(), true_label, false_label);
}

void CondBrInstruction::setFalseBranch(BasicBlock *bb)
{
    false_branch = bb;
}

BasicBlock *CondBrInstruction::getFalseBranch()
{
    return false_branch;
}

void CondBrInstruction::setTrueBranch(BasicBlock *bb)
{
    true_branch = bb;
}

BasicBlock *CondBrInstruction::getTrueBranch()
{
    return true_branch;
}

RetInstruction::RetInstruction(Operand *src, BasicBlock *insert_bb) : Instruction(RET, insert_bb)
{
    if(src != nullptr)
    {
        operands.push_back(src);
        src->addUse(this);
    }
}

RetInstruction::~RetInstruction()
{
    if(!operands.empty())
        operands[0]->removeUse(this);
}

void RetInstruction::output() const
{
    if(operands.empty())
    {
        fprintf(yyout, "  ret void\n");
    }
    else
    {
        std::string ret, type;
        ret = operands[0]->toStr();
        type = operands[0]->getType()->toStr();
        fprintf(yyout, "  ret %s %s\n", type.c_str(), ret.c_str());
    }
}

AllocaInstruction::AllocaInstruction(Operand *dst, SymbolEntry *se, BasicBlock *insert_bb) : Instruction(ALLOCA, insert_bb)
{
    operands.push_back(dst);
    dst->setDef(this);
    this->se = se;
}

AllocaInstruction::~AllocaInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
}

void AllocaInstruction::output() const
{
    std::string dst, type;
    dst = operands[0]->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "  %s = alloca %s, align 4\n", dst.c_str(), type.c_str());
}

LoadInstruction::LoadInstruction(Operand *dst, Operand *src_addr, BasicBlock *insert_bb) : Instruction(LOAD, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src_addr);
    dst->setDef(this);
    src_addr->addUse(this);
}

LoadInstruction::~LoadInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void LoadInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string src_type;
    std::string dst_type;
    dst_type = operands[0]->getType()->toStr();
    src_type = operands[1]->getType()->toStr();
    fprintf(yyout, "  %s = load %s, %s %s, align 4\n", dst.c_str(), dst_type.c_str(), src_type.c_str(), src.c_str());
}

StoreInstruction::StoreInstruction(Operand *dst_addr, Operand *src, BasicBlock *insert_bb) : Instruction(STORE, insert_bb)
{
    operands.push_back(dst_addr);
    operands.push_back(src);
    dst_addr->addUse(this);
    src->addUse(this);
}

StoreInstruction::~StoreInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
}

void StoreInstruction::output() const
{
    std::string dst = operands[0]->toStr();
    std::string src = operands[1]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string src_type = operands[1]->getType()->toStr();

    fprintf(yyout, "  store %s %s, %s %s, align 4\n", src_type.c_str(), src.c_str(), dst_type.c_str(), dst.c_str());
}

//函数调用 call
CallInstruction::CallInstruction(SymbolEntry *symbolentry,Operand *dst,vector<Operand*> vo, BasicBlock *insert_bb):Instruction(CALL,insert_bb){
    operands.push_back(dst);
    dst->addUse(this);
    this->vo=vo;
    names=symbolentry->toStr();
    if(((FunctionType*)(symbolentry->getType()))->getRetType()->isInt()==1)
        isvoid=0;   
    else if(((FunctionType*)(symbolentry->getType()))->getRetType()->isVoid()==1)
        isvoid=1;
    fprintf(stderr,"1\n");
};

CallInstruction::~CallInstruction(){
     operands[0]->removeUse(this);
};

void CallInstruction::output() const{
    //%18 = call i32 @funb(i32 1, i32 1)
    std::string str;
    std::string s1="  "+operands[0]->toStr();
    if(isvoid==0){
        str+=s1;
        str+=" = call i32 ";
       
    }
    else
        str+="  call void ";
    str+=names;
    str+="(";
    int i=0;
    for(Operand* o:vo){
        if(i!=0){
            str+=",";
        }
        if(!o->getType()->isArray()){
            str+=o->getType()->toStr();
        }
        else{
            str+=((ArrayType*)(o->getType()))->gettype()->toStr();
            str+="*";
        }
        str+=" ";
        str+=o->toStr();
        i++;
    }
    str+=")\n";
    fprintf(yyout,"%s",str.c_str());
};

//global
GlobalInstruction::GlobalInstruction(Operand *dst, Operand *src, BasicBlock *insert_bb) : Instruction(GLOBAL, insert_bb)
{
    operands.push_back(dst);
    dst->setDef(this);   

    if(src){
        operands.push_back(src);
        src->setDef(this);
    }
}

GlobalInstruction::~GlobalInstruction()
{
    // operands[0]->setDef(nullptr);
    // if(operands[0]->usersNum() == 0)
    //     delete operands[0];
}

void GlobalInstruction::output() const
{
    string dst = operands[0]->toStr();
    string type = operands[0]->getType()->toStr();
    if(operands.size()>1){
        string src=operands[1]->toStr();
        fprintf(yyout, "%s = global %s %s, align 4\n", dst.c_str(), type.c_str(), src.c_str());
    }
    else{
        fprintf(yyout, "%s = global %s, align 4\n", dst.c_str(), type.c_str());
    }
}

//强制转换
TypefixInstruction::TypefixInstruction(Operand* dst, Operand *src, BasicBlock *insert_bb) : Instruction(TYPEFIX, insert_bb)
{
    operands.push_back(dst);
    operands.push_back(src);
    dst->setDef(this);
    src->addUse(this);
}

TypefixInstruction::~TypefixInstruction()
{
    operands[0]->setDef(nullptr);
    if(operands[0]->usersNum() == 0)
        delete operands[0];
    operands[1]->removeUse(this);
}

void TypefixInstruction::output() const
{
    std::string dst, src, itype, btype;
    dst = operands[0]->toStr();
    src = operands[1]->toStr();
    itype=TypeSystem::intType->toStr();
    btype=TypeSystem::boolType->toStr();
    //%6 = zext i1 %5 to i32
    fprintf(yyout, "  %s = zext %s %s to %s\n", dst.c_str(), btype.c_str(), src.c_str(), itype.c_str());
}

//数组
ArrayItemFetchInstruction::ArrayItemFetchInstruction(Type* type, Operand *dst_addr, Operand* item_addr, Operand *offset, BasicBlock *insert_bb, bool f) : Instruction(ARRAYITEMFETCH, insert_bb)
{
    this->size = size;
    this->type = type;
    this->f = f;
    operands.push_back(dst_addr);//一个temp
    operands.push_back(item_addr);
    operands.push_back(offset);
    dst_addr->addUse(this);
    item_addr->addUse(this);
    offset->addUse(this);
}

ArrayItemFetchInstruction::~ArrayItemFetchInstruction()
{
    operands[0]->removeUse(this);
    operands[1]->removeUse(this);
    operands[2]->removeUse(this);
}

void ArrayItemFetchInstruction::output() const
{
    //cout<<"--------------------------------------------hi alloca"<<endl;
    std::string dst = operands[0]->toStr();
    std::string offset = operands[2]->toStr();
    std::string dst_type = operands[0]->getType()->toStr();
    std::string offset_type = operands[2]->getType()->toStr();

    //std::string array_type = arrayitem->getSymPtr()->getType()->toStr();
    // std::string item = (dynamic_cast<IdentifierSymbolEntry*>(arrayitem->getSymPtr()))->getAddr()->toStr();
    // std::string item_type = (dynamic_cast<IdentifierSymbolEntry*>(arrayitem->getSymPtr()))->getAddr()->getType()->toStr();
    std::string item = operands[1]->toStr();
    std::string item_type = operands[1]->getType()->toStr();

    std::string array_type=type->toStr();

    if(!f){
        fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s, i32 0, %s %s\n", dst.c_str(), array_type.c_str(), item_type.c_str(), item.c_str(), offset_type.c_str(), offset.c_str());
    }
    else{
        fprintf(yyout, "  %s = getelementptr inbounds %s, %s %s, %s %s\n", dst.c_str(), array_type.c_str(), item_type.c_str(), item.c_str(), offset_type.c_str(), offset.c_str());
    }
}

MachineOperand* Instruction::genMachineOperand(Operand* ope)
{
    auto se = ope->getEntry();
    MachineOperand* mope = nullptr;
    if(se->isConstant())
        mope = new MachineOperand(MachineOperand::IMM, dynamic_cast<ConstantSymbolEntry*>(se)->getValue());
    else if(se->isTemporary())
        mope = new MachineOperand(MachineOperand::VREG, dynamic_cast<TemporarySymbolEntry*>(se)->getLabel());
    else if(se->isVariable())
    {
        auto id_se = dynamic_cast<IdentifierSymbolEntry*>(se);
        if(id_se->isGlobal())
            mope = new MachineOperand(id_se->toStr().c_str());
        else
            exit(0);
    }
    return mope;
}

MachineOperand* Instruction::genMachineReg(int reg) 
{
    return new MachineOperand(MachineOperand::REG, reg);
}

MachineOperand* Instruction::genMachineVReg() 
{
    return new MachineOperand(MachineOperand::VREG, SymbolTable::getLabel());
}

MachineOperand* Instruction::genMachineImm(int val) 
{
    return new MachineOperand(MachineOperand::IMM, val);
}

MachineOperand* Instruction::genMachineLabel(int block_no)
{
    std::ostringstream buf;
    buf << ".L" << block_no;
    std::string label = buf.str();
    return new MachineOperand(label);
}

void AllocaInstruction::genMachineCode(AsmBuilder* builder)
{
    /* HINT:
    * Allocate stack space for local variabel
    * Store frame offset in symbol entry */
    cout<<"AllocaInstruction~!"<<endl;
    auto cur_func = builder->getFunction();
    int offset = cur_func->AllocSpace(4);
    dynamic_cast<TemporarySymbolEntry*>(operands[0]->getEntry())->setOffset(-offset);
}

void LoadInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"LoadInstruction~!"<<endl;
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;
    // Load global operand
    if(operands[1]->getEntry()->isVariable()
    && dynamic_cast<IdentifierSymbolEntry*>(operands[1]->getEntry())->isGlobal())
    {
        //cout<<1<<endl;
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);
        auto src = genMachineOperand(operands[1]);
        // example: load r0, addr_a
        cur_inst = new LoadMInstruction(cur_block, internal_reg1, src);
        cur_block->InsertInst(cur_inst);
        // example: load r1, [r0]
        cur_inst = new LoadMInstruction(cur_block, dst, internal_reg2);
        cur_block->InsertInst(cur_inst);
    }
    // Load local operand
    else if(operands[1]->getEntry()->isTemporary()
    && operands[1]->getDef()
    && operands[1]->getDef()->isAlloc())
    {
        //cout<<2<<endl;
        // example: load r1, [r0, #4]
        auto dst = genMachineOperand(operands[0]);
        auto src1 = genMachineReg(11);
        auto src2 = genMachineImm(dynamic_cast<TemporarySymbolEntry*>(operands[1]->getEntry())->getOffset());
        cur_inst = new LoadMInstruction(cur_block, dst, src1, src2);
        cur_block->InsertInst(cur_inst);
    }
    // Load operand from temporary variable
    else
    {
        //cout<<3<<endl;
        // example: load r1, [r0]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        cur_inst = new LoadMInstruction(cur_block, dst, src);
        cur_block->InsertInst(cur_inst);
    }
}

void StoreInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"StoreInstruction~!"<<endl;
    // TODO
    auto cur_block = builder->getBlock();
    MachineInstruction* cur_inst = nullptr;

    auto src = genMachineOperand(operands[1]);
    
    // Load global operand
    if(operands[1]->getEntry()->isConstant()){
        MachineOperand* tmp=genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, tmp, src);
        cur_block->InsertInst(cur_inst);
        src=tmp;
    }

    if(operands[0]->getEntry()->isVariable()
    && dynamic_cast<IdentifierSymbolEntry*>(operands[0]->getEntry())->isGlobal())
    {
        cout<<"isVariable"<<endl;
        auto dst = genMachineOperand(operands[0]);
        auto internal_reg1 = genMachineVReg();
        auto internal_reg2 = new MachineOperand(*internal_reg1);//加个方括号
        //auto src = genMachineOperand(operands[1]);
        // example: load r0, addr_a
        cur_inst = new LoadMInstruction(cur_block, internal_reg1, dst);
        cur_block->InsertInst(cur_inst);
        // example: load r1, [r0]
        cur_inst = new StoreMInstruction(cur_block, src, internal_reg2);
        cur_block->InsertInst(cur_inst);
    }
    // Load local operand
    else if(operands[0]->getEntry()->isTemporary()
    && operands[0]->getDef()
    && operands[0]->getDef()->isAlloc())//栈内变量
    {
        cout<<"isTemporary"<<endl;
        // example: load r1, [r0, #4]
        auto dst = genMachineOperand(operands[0]);
        //auto src = genMachineOperand(operands[1]);
        auto src1 = genMachineReg(11);//fp
        //这条有问题
        //dynamic_cast为什么会有问题？？？
        // cout<<"operands[1]?"<<((TemporarySymbolEntry*)(operands[1]->getEntry())==nullptr)<<endl;
        // cout<<"offset?"<<(dynamic_cast<TemporarySymbolEntry*>(operands[1]->getEntry())==nullptr)<<endl;
        auto src2 = genMachineImm(((TemporarySymbolEntry*)(operands[0]->getEntry()))->getOffset());
        cur_inst = new StoreMInstruction(cur_block, src, src1, src2);
        cur_block->InsertInst(cur_inst);
    }
    // Load operand from temporary variable
    else
    {
        cout<<"neither"<<endl;
        // example: load r1, [r0]
        auto dst = genMachineOperand(operands[0]);
        auto src = genMachineOperand(operands[1]);
        cur_inst = new StoreMInstruction(cur_block, src, dst);
        cur_block->InsertInst(cur_inst);
    }
    cout<<"store end---"<<endl;
}

void BinaryInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"BinaryInstruction~!"<<endl;
    // TODO:
    // complete other instructions
    auto cur_block = builder->getBlock();
    auto dst = genMachineOperand(operands[0]);
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    /* HINT:
    * The source operands of ADD instruction in ir code both can be immediate num.
    * However, it's not allowed in assembly code.
    * So you need to insert LOAD/MOV instrucrion to load immediate num into register.
    * As to other instructions, such as MUL, CMP, you need to deal with this situation, too.*/
    MachineInstruction* cur_inst = nullptr;
    if(src1->isImm())
    {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src1);
        cur_block->InsertInst(cur_inst);
        src1 = new MachineOperand(*internal_reg);
    }
    if(src2->isImm())
    {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src2);
        cur_block->InsertInst(cur_inst);
        src2 = new MachineOperand(*internal_reg);
    }
    
    MachineOperand* temp1 = genMachineVReg();
    MachineOperand* temp2 = genMachineVReg();

    //用于xor
    auto tr=genMachineImm(1);
    auto fl=genMachineImm(0);

    switch (opcode)
    {
    case ADD:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, dst, src1, src2);
        break;
    case SUB:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::SUB, dst, src1, src2);
        break;
    case MUL:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, dst, src1, src2);
        break;
    case DIV:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::DIV, dst, src1, src2);
        break;
    case MOD:
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::DIV, temp1, src1, src2);
        cur_block->InsertInst(cur_inst);
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::MUL, temp2, temp1, src2);
        cur_block->InsertInst(cur_inst);
        cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::SUB, dst, src1, temp2);
        break;
    case NOT:
        //cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::XOR, dst, src1, fl);
        cur_block->InsertInst(new CmpMInstruction(cur_block, src1, fl, CmpInstruction::E));
        cur_block->InsertInst(new MovMInstruction(cur_block, MovMInstruction::MOVEQ, dst, tr));
        cur_block->InsertInst(new MovMInstruction(cur_block, MovMInstruction::MOVNE, dst, fl));
        break;
    case SAME:
        //cur_inst = new BinaryMInstruction(cur_block, BinaryMInstruction::XOR, dst, src1, tr);
        break;
    default:
        break;
    }
    if(cur_inst)
        cur_block->InsertInst(cur_inst);
}

void CmpInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"CmpInstruction~!"<<endl;
    // TODO
    auto cur_block = builder->getBlock();
    auto src1 = genMachineOperand(operands[1]);
    auto src2 = genMachineOperand(operands[2]);
    MachineInstruction* cur_inst = nullptr;
    if (src1->isImm()) {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src1);
        cur_block->InsertInst(cur_inst);
        src1 = new MachineOperand(*internal_reg);
    }
    if (src2->isImm()) {
        auto internal_reg = genMachineVReg();
        cur_inst = new LoadMInstruction(cur_block, internal_reg, src2);
        cur_block->InsertInst(cur_inst);
        src2 = new MachineOperand(*internal_reg);
    }
    cur_inst = new CmpMInstruction(cur_block, src1, src2, opcode);
    cur_block->InsertInst(cur_inst);

    //保存必要的运算结果
    auto dst=genMachineOperand(operands[0]);
    auto tr=genMachineImm(1);
    auto fl=genMachineImm(0);
    switch (cur_block->get_op())
    {
        case CmpMInstruction::E:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVEQ, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVNE, dst, fl));
            break;
        case CmpMInstruction::NE:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVNE, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVEQ, dst, fl));
            break;
        case CmpMInstruction::L:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVLT, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVGE, dst, fl));
            break;
        case CmpMInstruction::LE:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVLE, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVGT, dst, fl));
            break;
        case CmpMInstruction::G:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVGT, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVLE, dst, fl));
            break;
        case CmpMInstruction::GE:
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVGE, dst, tr));
            cur_block->InsertInst(new MovMInstruction(cur_block,MovMInstruction::MOVLT, dst, fl));
            break;
        default:
            break;
    }
    // cur_inst=new MovMInstruction(cur_block,op, dst, tr);
    // cur_block->InsertInst(cur_inst);
}

void UncondBrInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"UncondInstruction~!"<<endl;
    // TODO
    auto cur_block = builder->getBlock();
    std::stringstream ss;
    ss << ".L" << branch->getNo();
    MachineOperand* dst = new MachineOperand(ss.str());
    MachineInstruction* cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst);
    cur_block->InsertInst(cur_inst);
}

void CondBrInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"CondInstruction~!"<<endl;
    // TODO
    auto cur_block = builder->getBlock();
    std::stringstream truess, falsess;
    //true 有条件
    truess << ".L" << true_branch->getNo();
    MachineOperand* dst = new MachineOperand(truess.str());
    MachineInstruction* cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst, cur_block->get_op());
    cur_block->InsertInst(cur_inst);
    //false 无条件
    falsess << ".L" << false_branch->getNo();
    dst = new MachineOperand(falsess.str());
    cur_inst = new BranchMInstruction(cur_block, BranchMInstruction::B, dst);
    cur_block->InsertInst(cur_inst);
}

void RetInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"RetInstruction~!"<<endl;
    // TODO
    /* HINT:
    * 1. Generate mov instruction to save return value in r0
    * 2. Restore callee saved registers and sp, fp
    * 3. Generate bx instruction */
   //存返回值
    auto cur_block = builder->getBlock();
    if(operands.size()>0){
        MachineOperand* r0 = new MachineOperand(MachineOperand::REG, 0);//0号寄存器
        MachineOperand* src = genMachineOperand(operands[0]);
        MachineInstruction* cur_inst = new MovMInstruction(cur_block, MovMInstruction::MOV, r0, src);//返回值放入0号寄存器
        cur_block->InsertInst(cur_inst);
    }
    //add指令 sp
    auto cur_func = builder->getFunction();
    auto sp = new MachineOperand(MachineOperand::REG, 13);//sp为13号寄存器
    cout<<cur_func->AllocSpace(0)<<endl;
    auto size = new MachineOperand(MachineOperand::IMM, cur_func->AllocSpace(0));
    MachineInstruction* add_sp = new BinaryMInstruction(cur_block, BinaryMInstruction::ADD, sp, sp, size, true);//bp置位！
    cur_block->InsertInst(add_sp);

    //对称pop
    auto fp = new MachineOperand(MachineOperand::REG, 11);
    auto lr = new MachineOperand(MachineOperand::REG, 14);
    MachineInstruction* pop1 = new StackMInstructon(nullptr, StackMInstructon::POP, lr);
    MachineInstruction* pop2 = new StackMInstructon(nullptr, StackMInstructon::POP, fp);
    cur_block->InsertInst(pop1);
    cur_block->InsertInst(pop2);

    //bx lr
    MachineInstruction* bx_lr = new BranchMInstruction(cur_block, BranchMInstruction::BX, lr);
    cur_block->InsertInst(bx_lr);
}

void CallInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"CallInstruction~!"<<endl;
    //Todo
    //暂时只考虑参数<=4的情况。
    auto cur_block=builder->getBlock();
    MachineInstruction* cur_inst=nullptr;
    if(vo.size()<=4){
        //放参数
        vector<MachineOperand*> mvo;
        int c=0;
        while(c<vo.size()){
            auto reg=new MachineOperand(MachineOperand::REG, c);
            auto param=genMachineOperand(vo[c]);
            cur_inst=new MovMInstruction(cur_block, MovMInstruction::MOV, reg, param);
            cur_block->InsertInst(cur_inst);
            c++;
        }
        //bl func
        const char *func_name = names.c_str() + 1;
        auto func_dst=new MachineOperand(func_name, true);
        cur_inst=new BranchMInstruction(cur_block, BranchMInstruction::BL, func_dst);
        cur_block->InsertInst(cur_inst);
        //mov r0 ..
        auto ret_dst=genMachineOperand(operands[0]);
        auto r0=new MachineOperand(MachineOperand::REG, 0);
        cur_inst=new MovMInstruction(cur_block, MovMInstruction::MOV, ret_dst, r0);
        cur_block->InsertInst(cur_inst);
    }
    cout<<"call end??"<<endl;
}

void GlobalInstruction::genMachineCode(AsmBuilder* builder)
{
    // cout<<"GlobalInstruction~!"<<endl;
    // auto cur_block = builder->getBlock();
    // MachineOperand* dst=new MachineOperand(operands[0]->toStr());
    // MachineOperand* src=nullptr;
    // if(operands.size()>1){
    //     src=new MachineOperand(operands[1]->toStr());
    // }
    // int size=((IntType*)(operands[0]->getEntry()->getType()))->getSize()/8;    
    // //cur_block->InsertInst(new GlobalMInstruction(cur_block, dst, src, size));
    // builder->getUnit()->globalList.push_back(new GlobalMInstruction(cur_block, dst, src, size));
    // cout<<"hi"<<endl;
}

void TypefixInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"TypefixInstruction~!"<<endl;
    auto cur_block=builder->getBlock();

    auto dst=genMachineOperand(operands[0]);
    auto src=genMachineOperand(operands[1]);
    
    auto tr=genMachineImm(1);
    int op;

    //{ E, NE, L, LE , G, GE, NONE }
    switch (cur_block->get_op())
    {
    case CmpMInstruction::E:
        op=MovMInstruction::MOVEQ;
        break;
    case CmpMInstruction::NE:
        op=MovMInstruction::MOVNE;
        break;
    case CmpMInstruction::L:
        op=MovMInstruction::MOVLT;
        break;
    case CmpMInstruction::LE:
        op=MovMInstruction::MOVLE;
        break;
    case CmpMInstruction::G:
        op=MovMInstruction::MOVGT;
        break;
    case CmpMInstruction::GE:
        op=MovMInstruction::MOVGE;
        break;
    default:
        break;
    }

    cout<<"op??"<<op<<endl;
    MachineInstruction* cur_inst=new MovMInstruction(cur_block,MovMInstruction::MOV, dst, src);

    cur_block->InsertInst(cur_inst);
}

void ArrayItemFetchInstruction::genMachineCode(AsmBuilder* builder)
{
    cout<<"ArrayItemFetchInstruction~!"<<endl;
}
