#ifndef HASHBLOCK_H
#define HASHBLOCK_H

/*
v1.0
Date:2016-04-20
Auth:skypigr@gmail.com
*/


#include "uint256.h"
#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_blake512_context     z_blake;
GLOBAL sph_bmw512_context       z_bmw;
GLOBAL sph_groestl512_context   z_groestl;
GLOBAL sph_jh512_context        z_jh;
GLOBAL sph_keccak512_context    z_keccak;
GLOBAL sph_skein512_context     z_skein;
GLOBAL sph_luffa512_context     z_luffa;
GLOBAL sph_cubehash512_context  z_cubehash;
GLOBAL sph_shavite512_context   z_shavite;
GLOBAL sph_simd512_context      z_simd;

#define fillz() do { \
    sph_blake512_init(&z_blake); \
    sph_bmw512_init(&z_bmw); \
    sph_groestl512_init(&z_groestl); \
    sph_jh512_init(&z_jh); \
    sph_keccak512_init(&z_keccak); \
    sph_skein512_init(&z_skein); \
    sph_luffa512_init(&z_luffa); \
    sph_cubehash512_init(&z_cubehash); \
    sph_shavite512_init(&z_shavite); \
    sph_simd512_init(&z_simd); \
} while (0) 


template<typename T1>
inline uint256 bthhash(const T1 pbegin, const T1 pend)
{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif
        
	uint512 mask = 12; // 0000...0000001100
    uint512 hash_zero = 0;
	uint512 hash_one = 4;
	uint512 hash_two = 8;
	uint512 hash_three = 12;
    

    uint512 hash[13];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[0]));
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, static_cast<const void*>(&hash[0]), 64);
    sph_bmw512_close(&ctx_bmw, static_cast<void*>(&hash[1]));

	if ((hash[1] & mask) == hash_zero)
	{
		sph_blake512_init(&ctx_blake);        
        sph_blake512 (&ctx_blake, static_cast<const void*>(&hash[1]), 64);
        sph_blake512_close(&ctx_blake, static_cast<void*>(&hash[2]));
	}
	else if((hash[1] & mask) == hash_one)
	{
		sph_groestl512_init(&ctx_groestl);
		sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[1]), 64);
		sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[2]));	
	}
	else if((hash[1] & mask) == hash_two)
	{
		sph_skein512_init(&ctx_skein);
		sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[1]), 64);
		sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[2]));
	}
	else
	{
		sph_jh512_init(&ctx_jh);
		sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[1]), 64);
		sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[2]));
	}
	
	
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[2]), 64);
    sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[3]));

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[3]), 64);
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[4]));
    
	if ((hash[4] & mask) == hash_zero)
	{
		sph_luffa512_init(&ctx_luffa);
		sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[4]), 64);
		sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[5]));    
	}
	else if((hash[4] & mask) == hash_one)
	{
		sph_groestl512_init(&ctx_groestl);
		sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[4]), 64);
		sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[5]));	
	}
	else if((hash[4] & mask) == hash_two)
	{
		sph_skein512_init(&ctx_skein);
		sph_skein512 (&ctx_skein, static_cast<const void*>(&hash[4]), 64);
		sph_skein512_close(&ctx_skein, static_cast<void*>(&hash[5]));
	}
	else
	{
		sph_keccak512_init(&ctx_keccak);
		sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[4]), 64);
		sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[5]));
	}
	
	
    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[5]), 64);
    sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[6]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[6]), 64);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[7]));


    
	if ((hash[7] & mask) == hash_zero)
	{
		sph_shavite512_init(&ctx_shavite);
		sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[7]), 64);
		sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[8])); 
	}
	else if((hash[7] & mask) == hash_one)
	{
		sph_groestl512_init(&ctx_groestl);
		sph_groestl512 (&ctx_groestl, static_cast<const void*>(&hash[7]), 64);
		sph_groestl512_close(&ctx_groestl, static_cast<void*>(&hash[8]));	
	}
	else if((hash[7] & mask) == hash_two)
	{
		sph_simd512_init(&ctx_simd);
		sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[7]), 64);
		sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[8]));
	}
	else
	{
		sph_keccak512_init(&ctx_keccak);
		sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[7]), 64);
		sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[8]));
	}
	
	
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[8]), 64);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[9]));
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[9]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[10]));
    
	if ((hash[10] & mask) == hash_zero)
	{
		sph_shavite512_init(&ctx_shavite);
		sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[10]), 64);
		sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[11])); 
	}
	else if((hash[10] & mask) == hash_one)
	{
		sph_jh512_init(&ctx_jh);
		sph_jh512 (&ctx_jh, static_cast<const void*>(&hash[10]), 64);
		sph_jh512_close(&ctx_jh, static_cast<void*>(&hash[11]));    
	}
	else if((hash[10] & mask) == hash_two)
	{
		sph_luffa512_init(&ctx_luffa);
		sph_luffa512 (&ctx_luffa, static_cast<void*>(&hash[10]), 64);
		sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[11]));
	}
	else
	{
		sph_keccak512_init(&ctx_keccak);
		sph_keccak512 (&ctx_keccak, static_cast<const void*>(&hash[10]), 64);
		sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[11]));
	}
	
    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[11]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[12]));

    return hash[12].trim256();
}

#endif // HASHBLOCK_H


