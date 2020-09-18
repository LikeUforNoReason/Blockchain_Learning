package main

import (
	"fmt"
	"strconv"
)

func (cli *CLI) print() {
	a := NewBlockchain()
	defer a.db.Close()

	b := a.Iterator()

	for {
		block := b.Next()

		fmt.Printf("Block: %x \n", block.Hash)
		fmt.Printf("Previous block: %x\n", block.Prev)
		c := NewProofOfWork(block)
		fmt.Printf("PoW: %s\n\n", strconv.FormatBool(c.Validate()))
		for _, tx := range block.Transactions {
			fmt.Println(tx)
		}
		fmt.Printf("\n\n")

		if len(block.Prev) == 0 {
			break
		}
	}
}
