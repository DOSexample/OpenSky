#include <GXD/Header.h>
#include <GXD/CHeader.h>

#define CLASS SKY_FOR_GXD

#define CALL( func, ... ) \
	CLASS* tMotion = reinterpret_cast<CLASS*>(motion); \
	tMotion->func( __VA_ARGS__ );

#define CALL_RET( func, ret, ... ) \
	CLASS* tMotion = reinterpret_cast<CLASS*>(motion); \
	ret = tMotion->func( __VA_ARGS__ );
