#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(32);
IntType TypeSystem::commonBool = IntType(1);
VoidType TypeSystem::commonVoid = VoidType();
ConstType TypeSystem::commonConst = ConstType(32);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;
Type* TypeSystem::constType =&commonConst;

// bool IntType::is_const()
// {
//     return false;
// }

// bool VoidType::is_const()
// {
//     return false;
// }
// bool FunctionType::is_const()
// {
//     return false;
// }
// bool PointerType::is_const()
// {
//     return false;
// }
std::string IntType::toStr()
{
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}

std::string VoidType::toStr()
{
    return "void";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "()";
    return buffer.str();
}

std::string ArrayType::toStr()
{
    std::ostringstream buffer;
    if(size!=-1){
        buffer << "[" << size <<" x " << type->toStr() <<"]";
    }
    else{
        buffer << type->toStr() <<"*";
    }
    return buffer.str();
}

std::string PointerType::toStr()
{
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}

std::string ConstType::toStr()
{
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}
