install golang compiler
# go build 
# ./blockchain
Usage:
  createblockchain -address ADDRESS - Create a blockchain and send genesis block reward to ADDRESS
  createwallet - Generates a new key-pair and saves it into the wallet file
  getbalance -address ADDRESS - Get balance of ADDRESS
  listaddresses - Lists all addresses from the wallet file
  print - Print all the blocks of the blockchain
  reindexutxo - Rebuilds the UTXO set
  send -from FROM -to TO -amount AMOUNT - Send AMOUNT of coins from FROM address to TO