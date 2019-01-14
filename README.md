# Implementation of Mirinae hash function

This is official implementation of Mirinae hash function used by [MicroBitcoin](https://github.com/MicroBitcoinOrg/MicroBitcoin).

## Motivation
Main motivation for development of this algo - create new ASICs resistant hash function which will replace Groestl512 after Baikal G28 appearance. Is uses combination of [groestl](http://www.groestl.info/) and [kupyna](https://github.com/sjinks/kupyna-c/) hash functions, source code can be checked [here](https://github.com/MicroBitcoinOrg/Mirinae/blob/master/mirinae.c#L10-L44).
Special thanks to **whitefire990**, **DigitalCruncher** and **Aiwe** for help with dicsussion/development of this algo.
Also cheers to Turtlecoin devs for [this](https://medium.com/@turtlecoin/introducing-cryptonight-soft-shell-2c2d4c497efd) article which Mirinae hash heavily inspired by :)

## Usage:
```
void mirinae(const void* input, void* output, size_t length, int height)
```

**input** - raw block header  
**output** - variable which receive hash output by `memcpy`  
**length** - data length  
**height** - new block height  

You can build demo app using this command:  
```
./build
```

and run it by:  
```
./mbc_hash
```

Developed with love by **iamstenman**
