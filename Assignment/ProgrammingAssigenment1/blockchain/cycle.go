package main

import (
	"log"

	"github.com/boltdb/bolt"
)

type BlockchainIterator struct {
	curHash []byte
	db          *bolt.DB
}

func (i *BlockchainIterator) Next() *Block {
	var block *Block

	err := i.db.View(func(tx *bolt.Tx) error {
		b := tx.Bucket([]byte(buckets))
		encodedBlock := b.Get(i.curHash)
		block = Disorder(encodedBlock)

		return nil
	})

	if err != nil {
		log.Panic(err)
	}

	i.curHash = block.Prev

	return block
}
