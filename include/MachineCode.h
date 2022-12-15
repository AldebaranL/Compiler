#ifndef __MACHINECODE_H__
#define __MACHINECODE_H__
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>
#include "SymbolTable.h"
#include "Type.h"

using namespace std;

/* Hint:
* MachineUnit: Compiler unit
* MachineFunction: Function in assembly code 
* MachineInstruction: Single assembly instruction  
* MachineOperand: Operand in assembly instruction, such as immediate number, register, address label */

/* Todo:
* We only give the example code of "class BinaryMInstruction" and "class AccessMInstruction" (because we believe in you !!!),
* You need to complete other the member function, especially "output()" ,
* After that, you can use "output()" to print assembly code . */

class MachineUnit;
class MachineFunction;
class MachineBlock;
class MachineInstruction;

class MachineOperand
{
private:
    MachineInstruction* parent;
    int type;
    int val;  // value of immediate number
    int reg_no; // register no
    std::string label; // address label
    bool isfunc;//区分label的打印
public:
    enum { IMM, VREG, REG, LABEL };
    MachineOperand(int tp, int val);
    MachineOperand(std::string label, bool isfunc=false);
    bool operator == (const MachineOperand&) const;
    bool operator < (const MachineOperand&) const;
    bool isImm() { return this->type == IMM; }; 
    bool isReg() { return this->type == REG; };
    bool isVReg() { return this->type == VREG; };
    bool isLabel() { return this->type == LABEL; };
    int getVal() {return this->val; };
    int getReg() {return this->reg_no; };
    void setReg(int regno) {this->type = REG; this->reg_no = regno;};
    std::string getLabel() {return this->label; };
    void setParent(MachineInstruction* p) { this->parent = p; };
    MachineInstruction* getParent() { return this->parent;};
    void PrintReg();
    void output();
};

class MachineInstruction
{
protected:
    MachineBlock* parent;
    int no;
    int type;  // Instruction type
    int cond = MachineInstruction::NONE;  // Instruction execution condition, optional !!
    int op;  // Instruction opcode
    // Instruction operand list, sorted by appearance order in assembly instruction
    std::vector<MachineOperand*> def_list;
    std::vector<MachineOperand*> use_list;
    void addDef(MachineOperand* ope) { def_list.push_back(ope); };
    void addUse(MachineOperand* ope) { use_list.push_back(ope); };
    // Print execution code after printing opcode
    void PrintCond();
    enum instType { BINARY, LOAD, STORE, MOV, BRANCH, CMP, STACK };
public:
    enum condType { E, NE, L, LE , G, GE, NONE };//和CmpInstruction保持统一 enum {E, NE, L, GE, G, LE};

    virtual void output() = 0;
    void setNo(int no) {this->no = no;};
    int getNo() {return no;};
    MachineBlock* getParent(){return parent;};
    std::vector<MachineOperand*>& getDef() {return def_list;};
    std::vector<MachineOperand*>& getUse() {return use_list;};

    bool isBinary(){return type==BINARY;};
    bool isStack(){return type==STACK;};
};

class BinaryMInstruction : public MachineInstruction
{
    bool bp;
public:
    enum opType { ADD, SUB, MUL, DIV, AND, OR };
    BinaryMInstruction(MachineBlock* p, int op, 
                    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, 
                    bool bp=false,
                    int cond = MachineInstruction::NONE);
    void output();
    bool isbp(){return bp;};
    void set_src2(MachineOperand* newsrc2){use_list[1]=newsrc2;};
};


class LoadMInstruction : public MachineInstruction
{
public:
    LoadMInstruction(MachineBlock* p,
                    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2 = nullptr, 
                    int cond = MachineInstruction::NONE);
    void output();
};

class StoreMInstruction : public MachineInstruction
{
public:
    StoreMInstruction(MachineBlock* p,
                    MachineOperand* src1, MachineOperand* src2, MachineOperand* src3 = nullptr, 
                    int cond = MachineInstruction::NONE);
    void output();
};

class MovMInstruction : public MachineInstruction
{
public:
    enum opType { MOV, MVN, MOVEQ, MOVNE, MOVGE, MOVGT, MOVLE, MOVLT };
    MovMInstruction(MachineBlock* p, int op, 
                MachineOperand* dst, MachineOperand* src,
                int cond = MachineInstruction::NONE);
    void output();
};

class BranchMInstruction : public MachineInstruction
{
public:
    enum opType { B, BL, BX };
    BranchMInstruction(MachineBlock* p, int op, 
                MachineOperand* dst, 
                int cond = MachineInstruction::NONE);
    void output();
};

class CmpMInstruction : public MachineInstruction
{
public:
    enum opType { CMP };
    CmpMInstruction(MachineBlock* p, 
                MachineOperand* src1, MachineOperand* src2, 
                int cond = MachineInstruction::NONE);
    void output();
};

class StackMInstructon : public MachineInstruction
{
public:
    enum opType { PUSH, POP };
    StackMInstructon(MachineBlock* p, int op, 
                vector<MachineOperand*> src_list,
                int cond = MachineInstruction::NONE);
    void output();
    void addSrc(vector<MachineOperand*> src_list);
    bool isPOP(){return op==POP;};
};

// class GlobalMInstruction : public MachineInstruction
// {
//     int size;
// public:
//     GlobalMInstruction(MachineBlock* p, 
//                 MachineOperand* dst,
//                 MachineOperand* src,
//                 int size,
//                 int cond = MachineInstruction::NONE);
//     void output();
// };

class MachineBlock
{
private:
    MachineFunction* parent;
    int no;  
    std::vector<MachineBlock *> pred, succ;
    std::vector<MachineInstruction*> inst_list;
    std::set<MachineOperand*> live_in;
    std::set<MachineOperand*> live_out;
    int opcode;//记录cmp的opcode
public:
    std::vector<MachineInstruction*>& getInsts() {return inst_list;};
    std::vector<MachineInstruction*>::iterator begin() { return inst_list.begin(); };
    std::vector<MachineInstruction*>::iterator end() { return inst_list.end(); };
    std::vector<MachineInstruction*>::reverse_iterator rbegin() { return inst_list.rbegin(); };
    MachineBlock(MachineFunction* p, int no) { this->parent = p; this->no = no; };
    void InsertInst(MachineInstruction* inst) { this->inst_list.push_back(inst); };
    void addPred(MachineBlock* p) { this->pred.push_back(p); };
    void addSucc(MachineBlock* s) { this->succ.push_back(s); };
    std::set<MachineOperand*>& getLiveIn() {return live_in;};
    std::set<MachineOperand*>& getLiveOut() {return live_out;};
    std::vector<MachineBlock*>& getPreds() {return pred;};
    std::vector<MachineBlock*>& getSuccs() {return succ;};
    MachineFunction* getParent(){return parent;};
    void output();
    void set_op(int op){this->opcode = op;};
    int get_op(){return this->opcode;};
};

class MachineFunction
{
private:
    MachineUnit* parent;
    std::vector<MachineBlock*> block_list;
    int stack_size;
    std::set<int> saved_regs;
    SymbolEntry* sym_ptr;
public:
    vector<MachineOperand*> src_list;

public:
    std::vector<MachineBlock*>& getBlocks() {return block_list;};
    std::vector<MachineBlock*>::iterator begin() { return block_list.begin(); };
    std::vector<MachineBlock*>::iterator end() { return block_list.end(); };
    MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr);
    /* HINT:
    * Alloc stack space for local variable;
    * return current frame offset ;
    * we store offset in symbol entry of this variable in function AllocInstruction::genMachineCode()
    * you can use this function in LinearScan::genSpillCode() */
    int AllocSpace(int size) { this->stack_size += size; return this->stack_size; };
    int getSize(){return this->stack_size; };
    void InsertBlock(MachineBlock* block) { this->block_list.push_back(block); };
    void addSavedRegs(int regno) {saved_regs.insert(regno);};
    void output();
};

class MachineUnit
{
private:
    std::vector<MachineFunction*> func_list;
    void PrintGlobalDecl();
    void PrintGlobalEnd();
public:
    std::vector<SymbolEntry*> global_dst;
    std::vector<SymbolEntry*> global_src;
public:
    std::vector<MachineFunction*>& getFuncs() {return func_list;};
    std::vector<MachineFunction*>::iterator begin() { return func_list.begin(); };
    std::vector<MachineFunction*>::iterator end() { return func_list.end(); };
    void InsertFunc(MachineFunction* func) { func_list.push_back(func);};
    void output();
};

#endif