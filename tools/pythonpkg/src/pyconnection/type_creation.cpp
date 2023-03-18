#include "duckdb_python/pyconnection.hpp"

namespace duckdb {

shared_ptr<DuckDBPyType> DuckDBPyConnection::MapType(shared_ptr<DuckDBPyType> key_type,
                                                     shared_ptr<DuckDBPyType> value_type) {
	auto map_type = LogicalType::MAP(key_type->Type(), value_type->Type());
	return make_shared<DuckDBPyType>(map_type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::ArrayType(shared_ptr<DuckDBPyType> type) {
	auto array_type = LogicalType::LIST(type->Type());
	return make_shared<DuckDBPyType>(array_type);
}

static child_list_t<LogicalType> GetChildList(const py::object &container) {
	child_list_t<LogicalType> types;
	if (py::isinstance<py::list>(container)) {
		const py::list &fields = container;
		idx_t i = 1;
		for (auto &item : fields) {
			if (!py::isinstance<DuckDBPyType>(item)) {
				string actual_type = py::str(item.get_type());
				throw InvalidInputException("object has to be a list of DuckDBPyType's, not '%s'", actual_type);
			}
			auto *pytype = item.cast<DuckDBPyType *>();
			types.push_back(std::make_pair(StringUtil::Format("v%d", i++), pytype->Type()));
		}
		return types;
	} else if (py::isinstance<py::dict>(container)) {
		const py::dict &fields = container;
		for (auto &item : fields) {
			auto &name_p = item.first;
			auto &type_p = item.second;
			string name = py::str(name_p);
			if (!py::isinstance<DuckDBPyType>(type_p)) {
				string actual_type = py::str(type_p.get_type());
				throw InvalidInputException("object has to be a list of DuckDBPyType's, not '%s'", actual_type);
			}
			auto *type = type_p.cast<DuckDBPyType *>();
			types.push_back(std::make_pair(name, type->Type()));
		}
		return types;
	} else {
		string actual_type = py::str(container.get_type());
		throw InvalidInputException(
		    "Can not construct a child list from object of type '%s', only dict/list is supported", actual_type);
	}
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::StructType(const py::object &fields) {
	bool is_list = py::isinstance<py::list>(fields);
	child_list_t<LogicalType> types = GetChildList(fields);
	if (types.empty()) {
		throw InvalidInputException("Can not create an empty struct type!");
	}
	auto struct_type = LogicalType::STRUCT(std::move(types));
	return make_shared<DuckDBPyType>(struct_type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::UnionType(const py::object &members) {
	child_list_t<LogicalType> types = GetChildList(members);

	if (types.empty()) {
		throw InvalidInputException("Can not create an empty union type!");
	}
	auto union_type = LogicalType::UNION(std::move(types));
	return make_shared<DuckDBPyType>(union_type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::EnumType(const string &name, shared_ptr<DuckDBPyType> type,
                                                      const py::list &values_p) {
	return nullptr;

	// vector<Value> values;
	// idx_t size = values_p.size();
	// values.reserve(size);

	//// Construct Value's out of the python objects
	// for (auto& item : values_p) {

	//}
	// if (values_p.empty()) {
	//	throw InvalidInputException("Can not create an empty ENUM type!");
	//}
	//// TODO: Create a Vector out of the vector of Values
	// Vector ordered_data(type->Type(), size);

	//// TODO: Sort this list, verify uniqueness

	// auto enum_type = LogicalType::ENUM(name, ordered_data, 0);
	// return make_shared<DuckDBPyType>(enum_type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::DecimalType(int width, int scale) {
	auto decimal_type = LogicalType::DECIMAL(width, scale);
	return make_shared<DuckDBPyType>(decimal_type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::StringType(const string &collation) {
	LogicalType type;
	if (collation.empty()) {
		type = LogicalType::VARCHAR;
	} else {
		type = LogicalType::VARCHAR_COLLATION(collation);
	}
	return make_shared<DuckDBPyType>(type);
}

shared_ptr<DuckDBPyType> DuckDBPyConnection::Type(const string &type_str) {
	if (!connection) {
		throw ConnectionException("Connection already closed!");
	}
	return make_shared<DuckDBPyType>(TransformStringToLogicalType(type_str, *connection->context));
}

} // namespace duckdb
