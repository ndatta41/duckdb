//===----------------------------------------------------------------------===//
// This file is automatically generated by scripts/generate_serialization.py
// Do not edit this file manually, your changes will be overwritten
//===----------------------------------------------------------------------===//

#include "duckdb/common/serializer/serializer.hpp"
#include "duckdb/common/serializer/deserializer.hpp"
#include "parquet_reader.hpp"
#include "parquet_reader.hpp"
#include "parquet_writer.hpp"
#include "parquet_writer.hpp"

namespace duckdb {

void ChildFieldIDs::Serialize(Serializer &serializer) const {
	serializer.WritePropertyWithDefault<case_insensitive_map_t<FieldID>>(100, "ids", ids);
}

ChildFieldIDs ChildFieldIDs::Deserialize(Deserializer &deserializer) {
	ChildFieldIDs result;
	deserializer.ReadPropertyWithDefault<case_insensitive_map_t<FieldID>>(100, "ids", result.ids);
	return result;
}

void FieldID::Serialize(Serializer &serializer) const {
	serializer.WritePropertyWithDefault<bool>(100, "set", set);
	serializer.WritePropertyWithDefault<int32_t>(101, "field_id", field_id);
	serializer.WriteProperty<ChildFieldIDs>(102, "child_field_ids", child_field_ids);
}

FieldID FieldID::Deserialize(Deserializer &deserializer) {
	FieldID result;
	deserializer.ReadPropertyWithDefault<bool>(100, "set", result.set);
	deserializer.ReadPropertyWithDefault<int32_t>(101, "field_id", result.field_id);
	deserializer.ReadProperty<ChildFieldIDs>(102, "child_field_ids", result.child_field_ids);
	return result;
}

void ParquetColumnDefinition::Serialize(Serializer &serializer) const {
	serializer.WritePropertyWithDefault<int32_t>(100, "field_id", field_id);
	serializer.WritePropertyWithDefault<string>(101, "name", name);
	serializer.WriteProperty<LogicalType>(103, "type", type);
	serializer.WriteProperty<Value>(104, "default_value", default_value);
}

ParquetColumnDefinition ParquetColumnDefinition::Deserialize(Deserializer &deserializer) {
	ParquetColumnDefinition result;
	deserializer.ReadPropertyWithDefault<int32_t>(100, "field_id", result.field_id);
	deserializer.ReadPropertyWithDefault<string>(101, "name", result.name);
	deserializer.ReadProperty<LogicalType>(103, "type", result.type);
	deserializer.ReadProperty<Value>(104, "default_value", result.default_value);
	return result;
}

void ParquetOptions::Serialize(Serializer &serializer) const {
	serializer.WritePropertyWithDefault<bool>(100, "binary_as_string", binary_as_string);
	serializer.WritePropertyWithDefault<bool>(101, "file_row_number", file_row_number);
	serializer.WriteProperty<MultiFileReaderOptions>(102, "file_options", file_options);
	serializer.WritePropertyWithDefault<vector<ParquetColumnDefinition>>(103, "schema", schema);
}

ParquetOptions ParquetOptions::Deserialize(Deserializer &deserializer) {
	ParquetOptions result;
	deserializer.ReadPropertyWithDefault<bool>(100, "binary_as_string", result.binary_as_string);
	deserializer.ReadPropertyWithDefault<bool>(101, "file_row_number", result.file_row_number);
	deserializer.ReadProperty<MultiFileReaderOptions>(102, "file_options", result.file_options);
	deserializer.ReadPropertyWithDefault<vector<ParquetColumnDefinition>>(103, "schema", result.schema);
	return result;
}

} // namespace duckdb
