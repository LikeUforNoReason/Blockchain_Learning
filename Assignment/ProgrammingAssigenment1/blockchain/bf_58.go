package main

import (
	"bytes"
	"math/big"
)

var bf_58 = []byte("123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz")

func Bf_58Encode(input []byte) []byte {
	var a []byte

	c := big.NewInt(0).SetBytes(input)

	d := big.NewInt(int64(len(bf_58)))
	e := big.NewInt(0)
	f := &big.Int{}

	for c.Cmp(e) != 0 {
		c.DivMod(c, d, f)
		a = append(a, bf_58[f.Int64()])
	}

	ReverseBytes(a)
	for b := range input {
		if b == 0x00 {
			a = append([]byte{bf_58[0]}, a...)
		} else {
			break
		}
	}

	return a
}

func Bf_58Decode(input []byte) []byte {
	a := big.NewInt(0)
	c := 0

	for b := range input {
		if b == 0x00 {
			c++
		}
	}

	d := input[c:]
	for _, b := range d {
		e := bytes.IndexByte(bf_58, b)
		a.Mul(a, big.NewInt(58))
		a.Add(a, big.NewInt(int64(e)))
	}

	result := a.Bytes()
	result = append(bytes.Repeat([]byte{byte(0x00)}, c), result...)

	return result
}
