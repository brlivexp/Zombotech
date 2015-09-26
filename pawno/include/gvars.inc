#define GLOBAL_VARTYPE_NONE (0)
#define GLOBAL_VARTYPE_INT (1)
#define GLOBAL_VARTYPE_STRING (2)
#define GLOBAL_VARTYPE_FLOAT (3)

native SetGVarInt(const name[], value, id = 0);
native GetGVarInt(const name[], id = 0);
native SetGVarString(const name[], const value[], id = 0);
native GetGVarString(const name[], dest[], maxlength = sizeof dest, id = 0);
native SetGVarFloat(const name[], Float:value, id = 0);
native Float:GetGVarFloat(const name[], id = 0);
native DeleteGVar(const name[], id = 0);
native GetGVarsUpperIndex(id = 0);
native GetGVarNameAtIndex(index, dest[], maxlength = sizeof dest, id = 0);
native GetGVarType(const name[], id = 0);