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
    const ullint modularDivisor(10000000000);
    ullint hash(modularDivisor);
    for(size_t i = 2; i < data.size(); ++i)
    {
      ullint tmp =  ullint(data[i]) * ullint(data[i-1]) * ullint(data[i-2]) * ullint(i);
      hash += tmp*tmp;
      if(hash > modularDivisor) hash %= modularDivisor;
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
  /** The block id. */
  int m_id;

  /** The data. */
  std::string m_data;

  /** The hash of the previous block. */
  ullint m_previousHash;

  /** The augmentation to the data required to generate a hash with the required properties. */
  ullint m_dataPerturbation;

  //##### CONSTRUCTORS #####
public:
  Block(const std::string& data, ullint previousHash)
  : m_data(data),
    m_previousHash(previousHash)
  {
    ++blockCount;
    m_id = blockCount;
    mine_hash(data);
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
    return HashUtil::calculate_dummy_hash(create_data_block(m_dataPerturbation, m_data, m_id));
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
  void mine_hash(const std::string& data)
  {
    const ullint m_largeInteger(100000);
    const bool verbose(true);

    if(verbose) std::cout << "mining blk: " << m_id;

    ullint dataPerturbation(m_largeInteger);
    ullint hash(0);
    do
    {
      const std::string dataBlock = create_data_block(++dataPerturbation, data, m_id);
      hash = HashUtil::calculate_dummy_hash(dataBlock);
      if(verbose && (dataPerturbation % m_largeInteger) == 0) std::cout << '.' << std::flush;
    }
    while((hash % m_largeInteger) != (m_largeInteger-1));

    m_dataPerturbation = dataPerturbation;

    if(verbose) std::cout << '\n';
  }

  /** Creates a data block by concatenating the data perturbation term, the actual data, and the block id. */
  std::string create_data_block(ullint dataPerturbation, const std::string& data, int blockId) const
  {
    return std::to_string(dataPerturbation) + data + std::to_string(blockId);
  }
};

/** Initialize the blockCount such that the id of the first block will be 0. */
int Block::blockCount = -1;

std::ostream& operator<<(std::ostream& os, const Block& blk)
{
  os << "-----------------------------------------\n";
  os << "prevHash: " << blk.get_previous_hash() << '\n';
  os << "block id: "<< blk.get_id() << "\n";
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

  /** Gets a block from the chain. */
  Block get_block(int blockId)
  {
    return m_blockChain[blockId];
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
  {
    ullint previousHash(0);
    if(i > 0) previousHash = blockchain.get_block(i-1).get_hash();

    Block block(data[i], previousHash);
    blockchain.add_block(block);
  }

  blockchain.verify();

  return 0;
}
