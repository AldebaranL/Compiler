#include "Unit.h"
#include "Type.h"
#include "Ast.h"
#include <iostream>

using namespace std;

extern FILE* yyout;

void Unit::insertFunc(Function *f)
{
    func_list.push_back(f);
}

void Unit::removeFunc(Function *func)
{
    func_list.erase(std::find(func_list.begin(), func_list.end(), func));
}

void Unit::output() const
{
    for(auto &inst : global_defs){
        cout<<"global"<<endl;
        inst->output();
    }
    for (auto &func : func_list)
        func->output();
    for (auto se : sysy_list) {
        cout<<"hi??"<<endl;
        FunctionType* type = (FunctionType*)(se->getType());
        std::string str = type->toStr();
        if(se->toStr()=="@getint"||se->toStr()=="@getch"){
            fprintf(yyout, "declare %s %s()\n", type->getRetType()->toStr().c_str(),
                se->toStr().c_str());
        }
        else{
            fprintf(yyout, "declare %s %s(i32)\n", type->getRetType()->toStr().c_str(),
                se->toStr().c_str());
        }
    }
    
}


void Unit::genMachineCode(MachineUnit* munit) 
{
    AsmBuilder* builder = new AsmBuilder();
    builder->setUnit(munit);
    for(auto &inst : global_defs){
        inst->genMachineCode(builder);
    }
    for (auto &func : func_list){
        func->genMachineCode(builder);
    }
}

Unit::~Unit()
{
    for(auto &func:func_list)
        delete func;
}


