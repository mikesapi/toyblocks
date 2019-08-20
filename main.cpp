#include <iostream>
#include <vector>
#include <string>

typedef unsigned long long int ullint;

/** This struct collects various hashing function utilities. */
struct HashUtil
{
  /** Calculates a hash for a string using a dummy hash algorithm. */
  static ullint calculate_dummy_hash(const std::string& data)
  {
    const ullint primeModularDivisor(1000000000100011);
    ullint hash(primeModularDivisor);
    for(size_t i = 2; i < data.size(); ++i)
    {
      ullint tmp =  ullint(data[i]) * ullint(data[i-1]) * ullint(data[i-2]) * ullint(i);
      hash += tmp*tmp;
      if(hash > primeModularDivisor) hash %= primeModularDivisor;
    }

    return hash;
  }
};

/** This class represents a single data block. */
class Block
{
  //##### PRIVATE STATIC VARIABLES #####
private:

  /** The number of data blocks that have been created. */
  static int blockCount;

  //##### PRIVATE VARIABLES #####
private:
  /** The data. */
  const std::string m_data;

  /** The augmentation to the data required to generate a hash with the required properties. */
  ullint m_puzzleResult;

  /** The block id. */
  int m_id;

  /** The hash of the previous block. */
  const ullint m_previousHash;

  //##### CONSTRUCTORS #####
public:
  Block(const std::string& data, ullint previousHash)
  : m_data(data),
    m_previousHash(previousHash)
  {
    ++blockCount;
    m_id = blockCount;
    m_puzzleResult = mine_hash();
  }

  //##### PUBLIC MEMBER FUNCTIONS #####
public:

  /** Gets the Id of this block. */
  int get_id() const
  {
    return m_id;
  }

  /** Gets the data in this block. */
  std::string get_data() const
  {
    return m_data;
  }

  /** Gets the hash of this block. */
  ullint get_hash() const
  {
    return HashUtil::calculate_dummy_hash(create_data_block(m_puzzleResult, m_previousHash, m_data, m_id));
  }

  /** Gets the hash of the previous block. */
  ullint get_previous_hash() const
  {
    return m_previousHash;
  }

  //##### PRIVATE MEMBER FUNCTIONS #####
private:

  /** Mines an appropriate hash value by augmenting the data in the block,
   *  The last 5 digits of the hash should all be 9's.
   */
  ullint mine_hash()
  {
    const ullint m_largeInteger(1000000);
    const bool verbose(true);

    if(verbose) std::cout << "mining blk: " << m_id;

    ullint puzzleResult(m_largeInteger);
    ullint hash(0);
    do
    {
      hash = HashUtil::calculate_dummy_hash(create_data_block(++puzzleResult, m_previousHash, m_data, m_id));
      if(verbose && (puzzleResult % 100000) == 0) std::cout << '.' << std::flush;
    }
    while((hash % m_largeInteger) != (m_largeInteger-1));
    if(verbose) std::cout << '\n';

    return puzzleResult;
  }

  /** Creates a data block by concatenating the data puzzle result, the previous bloc hash, the actual data, and the block id. */
  std::string create_data_block(ullint puzzleResult, ullint previousHash, const std::string& data, int blockId) const
  {
    std::string dataBlock = "blockId-" + std::to_string(blockId)
                          + "--data-\"" + data + "\""
                          + "--previousHash-" + std::to_string(previousHash)
                          + "--puzzleResult-" + std::to_string(puzzleResult);
    return dataBlock;
  }
};

/** Initialize the blockCount such that the id of the first block will be 0. */
int Block::blockCount = -1;

std::ostream& operator<<(std::ostream& os, const Block& blk)
{
  os << "-----------------------------------------\n";
  os << "prevHash: " << blk.get_previous_hash() << '\n';
  os << "block id: " << blk.get_id() << "\n";
  os << "    data: " << blk.get_data() << '\n';
  os << "    hash: " << blk.get_hash() << '\n';
  os << "-----------------------------------------";
  return os;
}

/** This class represents a chain of data blocks. */
class BlockChain
{
  //##### PRIVATE VARIABLES #####
private:
  /** The block chain. */
  std::vector<Block> m_blockChain;

  //##### PUBLIC MEMBER FUNCTIONS #####
public:
  /** Adds a data block to the chain. */
  void add_block(const Block& block)
  {
    m_blockChain.push_back(block);
  }

  //##### CONSTRUCTORS #####
public:
  /** Creates a new blockchain. */
  BlockChain()
  {
    Block genesisBlock = Block("## GenesisBlock ##", 0);
    add_block(genesisBlock);
  }

  /** Gets a block from the chain. */
  Block get_block(int blockId)
  {
    return m_blockChain[blockId];
  }

  ullint get_latest_hash()
  {
    return m_blockChain.back().get_hash();
  }

  /** Verifies that the block chain is valid by comparing the hash values of adjacent blocks. */
  void verify()
  {
    std::cout << "\n\nVerifying Blockchain:\n\n";
    for(size_t i = 1; i < m_blockChain.size(); ++i)
    {
      ullint previousHashStamp = get_block(i).get_previous_hash();
      ullint previousHash = get_block(i-1).get_hash();
      std::cout << get_block(i-1);
      if(previousHashStamp == previousHash)
      {
        std::cout << "  <GOOD>\n";
      }
      else
      {
        std::cout << "  <BAD>\n";
      }
    }
  }
};

int main()
{
  std::cout << "A simple blockchain toy example.\n\n";

  std::vector<std::string> data;
  data.push_back("Tomorrow, and tomorrow, and tomorrow,");
  data.push_back("Creeps in this petty pace from day to day,");
  data.push_back("To the last syllable of recorded time;");
  data.push_back("And all our yesterdays have lighted fools");
  data.push_back("The way to dusty death. Out, out, brief candle!");
  data.push_back("Life's but a walking shadow, a poor player,");
  data.push_back("That struts and frets his our upon the stage,");
  data.push_back("And then is heard no more. It is a tale");
  data.push_back("Told by an idiot, full of sound and fury,");
  data.push_back("Signifying nothing.");
  data.push_back("------ The End ------");

  BlockChain blockchain;
  for(size_t i = 0; i < data.size(); ++i)
    blockchain.add_block(Block(data[i], blockchain.get_latest_hash()));

  blockchain.verify();

  return 0;
}
