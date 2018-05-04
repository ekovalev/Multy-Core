#ifndef MULTY_TRANSACTION_ETHEREUM_TRANSACTION_H
#define MULTY_TRANSACTION_ETHEREUM_TRANSACTION_H

#include "multy_core/ethereum.h"

#include "multy_core/src/transaction_base.h"
#include "multy_core/src/api/properties_impl.h"

namespace multy_core
{
namespace internal
{
struct EthereumTransactionFee;
struct EthereumTransactionSource;
struct EthereumTransactionDestination;
struct EthereumTransactionSignature;
struct EthereumDataStream;
struct EthereumTokenTransferData;

typedef std::unique_ptr<EthereumTransactionFee> EthereumTransactionFeePtr;
typedef std::unique_ptr<EthereumTransactionSource> EthereumTransactionSourcePtr;
typedef std::unique_ptr<EthereumTransactionDestination> EthereumTransactionDestinationPtr;
typedef std::unique_ptr<EthereumTransactionSignature> EthereumTransactionSignaturePtr;
typedef std::unique_ptr<EthereumTokenTransferData> EthereumTokenTransferDataPtr;

class EthereumTransaction : public TransactionBase
{
public:
    explicit EthereumTransaction(const Account& account);
    virtual ~EthereumTransaction();

    BinaryDataPtr serialize() override;
    BigInt get_total_spent() const override;
    BigInt get_total_fee() const override;

    void verify();
    void update() override;
    void sign();
    BigInt estimate_total_fee(size_t sources_count, size_t destinations_count) const override;

    Properties& add_source() override;
    Properties& add_destination() override;
    Properties& get_fee() override;
    void set_message(const BinaryData& value) override;

private:
    enum SerializationMode
    {
        SERIALIZE,
        SERIALIZE_WITH_SIGNATURE,
        SERIALIZE_WITH_CHAIN_ID,
    };
    void serialize_to_stream(EthereumDataStream& stream, SerializationMode mode) const;
    void on_token_transfer_set(const std::string& value);

private:
    const Account& m_account;

    PropertyT<BigInt> m_nonce;
    const EthereumChainId m_chain_id;
    PropertyT<std::string> m_token_transfer;

    EthereumTransactionFeePtr m_fee;
    EthereumTransactionSourcePtr m_source;
    EthereumTransactionDestinationPtr m_destination;
    EthereumTokenTransferDataPtr m_token_transfer_data;
    EthereumTransactionSignaturePtr m_signature;
    BinaryDataPtr m_payload;

    BigInt m_gas;
};

} // namespace internal
} // namespace multy_core

#endif // MULTY_TRANSACTION_ETHEREUM_TRANSACTION_H
