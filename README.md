# Implementation of Mirinae hash function

This is official implementation of Mirinae hash function used by [MicroBitcoin](https://github.com/MicroBitcoinOrg/MicroBitcoin).

## Motivation
Main motivation for development of this algo - create new ASICs resistant hash function which will replace Groestl512 after Baikal G28 appearance.  
Special thanks to **whitefire990**, **DigitalCruncher** and **Aiwe** for help with dicsussion/development of this algo.
Also cheers to Turtlecoin devs for [this](https://medium.com/@turtlecoin/introducing-cryptonight-soft-shell-2c2d4c497efd) article which Mirinae hash heavily inspired by :)

## Usage:

```
mirinae(const void* data, size_t length, void* output, int height, const void* seed)
```

**data** - raw block header  
**length** - data length  
**output** - variable which receive hash output by `memcpy`  
**height** - new block height  
**seed** - arbitrary data with length 64 (recomended to use previous block hash)  

You can build demo app using this command:  
```
./build
```

and run it by:  
```
./mbc_hash
```

Developed with love by **iamstenman**
