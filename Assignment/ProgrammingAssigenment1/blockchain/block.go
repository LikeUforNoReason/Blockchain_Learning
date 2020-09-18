package main

import (
	"bytes"
	"encoding/gob"
	"log"
	"time"
)

type Block struct {
	Timestamp     int64
	Transactions  []*Transaction
	Prev []byte
	Hash          []byte
	Nonce         int
}

func NewBlock(transactions []*Transaction, prev []byte) *Block {
	result := &Block{time.Now().Unix(), transactions, prev, []byte{}, 0}
	a := NewProofOfWork(result)
	b, c := a.Run()

	result.Hash = c[:]
	result.Nonce = b

	return result
}

func GenesisBlock(coinbase *Transaction) *Block {
	return NewBlock([]*Transaction{coinbase}, []byte{})
}

func (b *Block) Txhash() []byte {
	var txs [][]byte

	for _, tx := range b.Transactions {
		txs = append(txs, tx.Order())
	}
	a := NewMerkleTree(txs)

	return a.RootNode.Data
}

func (b *Block) Order() []byte {
	var a bytes.Buffer
	c := gob.NewEncoder(&a)

	d := c.Encode(b)
	if d != nil {
		log.Panic(d)
	}

	return a.Bytes()
}

func Disorder(d []byte) *Block {
	var a Block

	b := gob.NewDecoder(bytes.NewReader(d))
	c := b.Decode(&a)
	if c != nil {
		log.Panic(c)
	}

	return &a
}
