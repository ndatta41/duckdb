#include "duckdb/common/enums/compression_type.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"

namespace duckdb {

CompressionType CompressionTypeFromString(const string &str) {
	auto compression = StringUtil::Lower(str);
	if (compression == "uncompressed") {
		return CompressionType::COMPRESSION_UNCOMPRESSED;
	} else if (compression == "rle") {
		return CompressionType::COMPRESSION_RLE;
	} else if (compression == "dictionary") {
		return CompressionType::COMPRESSION_DICTIONARY;
	} else if (compression == "pfor") {
		return CompressionType::COMPRESSION_PFOR_DELTA;
	} else if (compression == "bitpacking") {
		return CompressionType::COMPRESSION_BITPACKING;
	} else if (compression == "fsst") {
		return CompressionType::COMPRESSION_FSST;
	} else {
		return CompressionType::COMPRESSION_INVALID;
	}
}

string CompressionTypeToString(CompressionType type) {
	switch(type) {
	case CompressionType::COMPRESSION_UNCOMPRESSED:
		return "Uncompressed";
	case CompressionType::COMPRESSION_CONSTANT:
		return "Constant";
	case CompressionType::COMPRESSION_RLE:
		return "RLE";
	case CompressionType::COMPRESSION_DICTIONARY:
		return "Dictionary";
	case CompressionType::COMPRESSION_PFOR_DELTA:
		return "PFOR";
	case CompressionType::COMPRESSION_BITPACKING:
		return "BitPacking";
	case CompressionType::COMPRESSION_FSST:
		return "FSST";
	default:
		throw InternalException("Unrecognized compression type!");
	}

}

}
