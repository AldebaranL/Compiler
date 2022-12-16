#include "MachineCode.h"

#include <iostream>
using namespace std;

extern FILE* yyout;

MachineOperand::MachineOperand(int tp, int val)
{
    this->type = tp;
    if(tp == MachineOperand::IMM)
        this->val = val;
    else 
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label, bool isfunc)
{
    this->type = MachineOperand::LABEL;
    this->label = label;
    this->isfunc=isfunc;
}

bool MachineOperand::operator==(const MachineOperand&a) const
{
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand&a) const
{
    if(this->type == a.type)
    {
        if(this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

void MachineOperand::PrintReg()
{
    switch (reg_no)
    {
    case 11:
        fprintf(yyout, "fp");
        break;
    case 13:
        fprintf(yyout, "sp");
        break;
    case 14:
        fprintf(yyout, "lr");
        break;
    case 15:
        fprintf(yyout, "pc");
        break;
    default:
        fprintf(yyout, "r%d", reg_no);
        break;
    }
}

void MachineOperand::output() 
{
    /* HINT：print operand
    * Example:
    * immediate num 1 -> print #1;
    * register 1 -> print r1;
    * lable addr_a -> print addr_a; */
    switch (this->type)
    {
    case IMM:
        fprintf(yyout, "#%d", this->val);
        break;
    case VREG:
        fprintf(yyout, "v%d", this->reg_no);
        break;
    case REG:
        PrintReg();
        break;
    case LABEL:
        if(isfunc)
            fprintf(yyout, "%s", this->label.c_str());
        else if (this->label.substr(0, 2) == ".L")
            fprintf(yyout, "%s", this->label.c_str());
        else
            fprintf(yyout, "addr_%s", (char*)(this->label.c_str())+1);
    default:
        break;
    }
}

void MachineInstruction::PrintCond()
{
    // TODO
    switch (cond) {
        case E:
            fprintf(yyout, "eq");
            break;
        case NE:
            fprintf(yyout, "ne");
            break;
        case L:
            fprintf(yyout, "lt");
            break;
        case LE:
            fprintf(yyout, "le");
            break;
        case G:
            fprintf(yyout, "gt");
            break;
        case GE:
            fprintf(yyout, "ge");
            break;
        default:
            break;
    }
}

BinaryMInstruction::BinaryMInstruction(
    MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, 
    bool bp,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BINARY;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    src2->setParent(this);

    this->bp=bp;//是否回填
}

void BinaryMInstruction::output() 
{
    // TODO: 
    // Complete other instructions
    switch (this->op)
    {
    case BinaryMInstruction::ADD:
        fprintf(yyout, "\tadd ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::SUB:
        fprintf(yyout, "\tsub ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::MUL:
        fprintf(yyout, "\tmul ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::DIV:
        fprintf(yyout, "\tsdiv ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    // case BinaryMInstruction::XOR:
    //     fprintf(yyout, "\txor ");
    //     this->PrintCond();
    //     this->def_list[0]->output();
    //     fprintf(yyout, ", ");
    //     this->use_list[0]->output();
    //     fprintf(yyout, ", ");
    //     this->use_list[1]->output();
    //     fprintf(yyout, "\n");
    //     break;
    default:
        break;
    }
}

LoadMInstruction::LoadMInstruction(MachineBlock* p,
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::LOAD;
    this->op = -1;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    if (src2)
        this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    if (src2)
        src2->setParent(this);
}

void LoadMInstruction::output()
{
    fprintf(yyout, "\tldr ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");

    // Load immediate num, eg: ldr r1, =8
    if(this->use_list[0]->isImm())
    {
        fprintf(yyout, "=%d\n", this->use_list[0]->getVal());
        return;
    }

    // Load address
    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "[");

    this->use_list[0]->output();
    if( this->use_list.size() > 1 )
    {
        fprintf(yyout, ", ");
        this->use_list[1]->output();
    }

    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

StoreMInstruction::StoreMInstruction(MachineBlock* p,
    MachineOperand* src1, MachineOperand* src2, MachineOperand* src3, 
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::STORE;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    if (src3)
        this->use_list.push_back(src3);
    src1->setParent(this);
    src2->setParent(this);
    if (src3)
        src3->setParent(this);
}

void StoreMInstruction::output()
{
    // TODO
    fprintf(yyout, "\tstr ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");

    // Store address
    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "[");

    this->use_list[1]->output();
    if( this->use_list.size() > 2 )
    {
        fprintf(yyout, ", ");
        this->use_list[2]->output();//打印名字？
    }

    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");
}

MovMInstruction::MovMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src,
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::MOV;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

void MovMInstruction::output() 
{
    // TODO
    switch (this->op) {
        case MOV:
            fprintf(yyout, "\tmov");
            break;
        case MOVEQ:
            fprintf(yyout, "\tmoveq");
            break;
        case MOVNE:
            fprintf(yyout, "\tmovne");
            break;
        case MOVGE:
            fprintf(yyout, "\tmovge");
            break;
        case MOVGT:
            fprintf(yyout, "\tmovgt");
            break;
        case MOVLE:
            fprintf(yyout, "\tmovle");
            break;
        case MOVLT:
            fprintf(yyout, "\tmovlt");
            break;
        default:
            break;
    }
    PrintCond();
    fprintf(yyout, " ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");
}

BranchMInstruction::BranchMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, 
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::BRANCH;
    this->op = op;
    this->cond = cond;
    this->use_list.push_back(dst);
    dst->setParent(this);
}

void BranchMInstruction::output()
{
    // TODO
    switch (op) {
        case B:
            fprintf(yyout, "\tb");
            break;
        case BX:
            fprintf(yyout, "\tbx");
            break;
        case BL:
            fprintf(yyout, "\tbl");
            break;
    }
    PrintCond();
    fprintf(yyout, " ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");
}

CmpMInstruction::CmpMInstruction(MachineBlock* p, 
    MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::CMP;
    this->op = op;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    src1->setParent(this);
    src2->setParent(this);

    p->set_op(cond);//为condbr记录opcode
    cout<<"----cond:"<<cond<<endl;
}

void CmpMInstruction::output()
{
    // TODO
    // Jsut for reg alloca test
    // delete it after test
    switch (this->op) {
        case CmpMInstruction::CMP:
            fprintf(yyout, "\tcmp ");
            break;
        default:
            break;
    }
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}

StackMInstructon::StackMInstructon(MachineBlock* p, int op, 
    vector<MachineOperand*> src_list,
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    if (!src_list.empty()) {
        for(auto& src:src_list){
            this->use_list.push_back(src);
            src->setParent(this);
        }
    }
}

void StackMInstructon::addSrc(vector<MachineOperand*> src_list){
    if (!src_list.empty()) {
        for(auto& src:src_list){
            this->use_list.push_back(src);
            src->setParent(this);
        }
    }
}

void StackMInstructon::output()
{
    // TODO
    if (!this->use_list.empty()) {
        switch (op) {
            case PUSH:
                fprintf(yyout, "\tpush ");
                break;
            case POP:
                fprintf(yyout, "\tpop ");
                break;
            default:
                break;
        }
        fprintf(yyout, "{");
        if (!use_list.empty()) {
            for(auto& src:use_list){
                src->output();
                if(src!=use_list.back())
                    fprintf(yyout, ", ");
            }
        } 
        fprintf(yyout, "}\n");
    }
}

// GlobalMInstruction::GlobalMInstruction(MachineBlock* p,
//     MachineOperand* dst,
//     MachineOperand* src,
//     int size,
//     int cond)
// {
//     // TODO
//     this->parent = p;
//     this->type = MachineInstruction::STACK;
//     this->op = op;
//     this->size=size;
//     this->cond = cond;
//     this->use_list.push_back(dst);
//     if (src) {
//         this->use_list.push_back(src);
//         src->setParent(this);
//     }
// }

// void GlobalMInstruction::output()
// {
//     // TODO
//     if (!this->use_list.empty()) {
//         fprintf(yyout, "\t.global %s\n", use_list[0]->getLabel().c_str());
//         fprintf(yyout, "\t.align 4\n");
//         fprintf(yyout, "\t.size %s, %d\n", use_list[0]->getLabel().c_str(), size);
//         fprintf(yyout, "%s:\n", use_list[0]->getLabel().c_str());
//         fprintf(yyout, "\t.word %s", use_list[1]->getLabel().c_str());
//     }
// }

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) 
{ 
    this->parent = p; 
    this->sym_ptr = sym_ptr; 
    this->stack_size = 0;
};

void MachineBlock::output()
{
    fprintf(yyout, ".L%d:\n", this->no);
    //cout<<"total:"<<inst_list.size()<<endl;
    int count=0;
    for(auto inst : inst_list){
        // cout<<"count: "<<count<<endl;
        // cout<<"-----------inst?"<<(inst==nullptr)<<endl;
        // cout<<"isBinary?"<<inst->isBinary()<<endl;
        // cout<<"isbp?"<<((BinaryMInstruction*)inst)->isbp()<<endl;
        if(inst->isBinary()&&((BinaryMInstruction*)inst)->isbp()){
            //说明是return语句的add sp
            cout<<"?????"<<parent->AllocSpace(0)<<endl;
            ((BinaryMInstruction*)inst)->set_src2(new MachineOperand(MachineOperand::IMM, parent->AllocSpace(0)));
        }
        if(inst->isStack()&&((StackMInstructon*)inst)->isPOP()){
            //说明是return语句的add sp
            ((StackMInstructon*)inst)->addSrc(parent->src_list);
        }
        // cout<<"count: "<<count<<endl;
        inst->output();
        // cout<<"count: "<<count++<<endl;
    }
    if(inst_list.empty()){
        
    }
}

void MachineFunction::output()
{
    const char *func_name = this->sym_ptr->toStr().c_str() + 1;//what???
    fprintf(yyout, "\t.global %s\n", func_name);
    fprintf(yyout, "\t.type %s , %%function\n", func_name);
    fprintf(yyout, "%s:\n", func_name);
    // TODO
    /* Hint:
    *  1. Save fp
    *  2. fp = sp
    *  3. Save callee saved register
    *  4. Allocate stack space for local variable */
    
    // Traverse all the block in block_list to print assembly code.

    auto fp = new MachineOperand(MachineOperand::REG, 11);
    auto sp = new MachineOperand(MachineOperand::REG, 13);
    auto lr = new MachineOperand(MachineOperand::REG, 14);

    for(auto& reg:saved_regs){
        auto r=new MachineOperand(MachineOperand::REG, reg);
        src_list.push_back(r);
    }
    src_list.push_back(fp);
    src_list.push_back(lr);
    (new StackMInstructon(nullptr, StackMInstructon::PUSH, src_list))->output();
    (new MovMInstruction(nullptr, MovMInstruction::MOV, fp, sp))->output();
    int off = AllocSpace(0);
    if (off % 8 != 0) {
        off = AllocSpace(4);
    }
    if (off) {
        auto size = new MachineOperand(MachineOperand::IMM, off);       
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, size))->output();
    }

    for(auto iter : block_list)
        iter->output();
}

void MachineUnit::PrintGlobalDecl()
{
    // TODO:
    // You need to print global variable/const declarition code;
    if (!global_dst.empty())
        fprintf(yyout, "\t.data\n");
    
    for(int i=0;i<(int)(global_dst.size());i++){
        const char * name=((IdentifierSymbolEntry*)(global_dst[i]))->toStr().c_str()+1;
        int size=((IntType*)(global_dst[i]->getType()))->getSize()/8;
        
        if(global_dst[i]->getType()->isConst()){
            fprintf(yyout, "\t.section .rodata\n");
        }
        //cout<<"name????????"<<name<<endl;???为什么??????????
        fprintf(yyout, "\t.global %s\n", name);
        fprintf(yyout, "\t.align 4\n");
        fprintf(yyout, "\t.size %s, %d\n", name, size);
        fprintf(yyout, "%s:\n", name);
        
        string val;
        if(global_src[i]&&global_src[i]->isConstant()){
            val=global_src[i]->toStr();
        }
        else{
            val="0";
        }

        fprintf(yyout, "\t.word %s\n", val.c_str());
    }
}
void MachineUnit::PrintGlobalEnd()
{
    for(int i=0;i<(int)(global_dst.size());i++){
        const char * name=((IdentifierSymbolEntry*)(global_dst[i]))->toStr().c_str()+1;
        
        fprintf(yyout, "addr_%s:\n", name);
        fprintf(yyout, "\t.word %s\n", name);
    }
}

void MachineUnit::output()
{
    // TODO
    /* Hint:
    * 1. You need to print global variable/const declarition code;
    * 2. Traverse all the function in func_list to print assembly code;
    * 3. Don't forget print bridge label at the end of assembly code!! */
    fprintf(yyout, "\t.arch armv8-a\n");
    fprintf(yyout, "\t.arch_extension crc\n");
    fprintf(yyout, "\t.arm\n");
    PrintGlobalDecl();
    fprintf(yyout, "\t.text\n");
    for(auto iter : func_list)
        iter->output();
    fprintf(yyout, "\n");
    PrintGlobalEnd();
}
