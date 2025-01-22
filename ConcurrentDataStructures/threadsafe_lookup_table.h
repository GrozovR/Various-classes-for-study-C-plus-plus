// TODO: description

#pragma once
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <shared_mutex>
#include <vector>

namespace CDS {

template<typename Key, typename Value, typename Hash=std::hash<Key>>
class threadsafe_lookup_table
{
public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef Hash hash_type;

	threadsafe_lookup_table(size_t num_buckets = 19, const Hash& _hasher = Hash())
		: buckets(num_buckets), hasher(_hasher)
	{
		for (size_t i{ 0 }; i < num_buckets; i++) {
			buckets[i].reset( new bucket_type);
		}
	}
	threadsafe_lookup_table(const threadsafe_lookup_table&) = delete;
	threadsafe_lookup_table& operator=(const threadsafe_lookup_table&) = delete;

	Value value_for(const Key& key, const Value& def_val) const
	{
		return get_bucket(key).value_for(key, def_val);
	}
	
	void get_or_update(const Key& key, const Value& def_val)
	{
		get_bucket(key).add_or_update_mapping(key, def_val);
	}
	
	void remove(const Key& key)
	{
		get_bucket(key).remove_mapping(key);
	}

	std::map<Key, Value> get_map() const
	{
		std::vector<std::unique_lock<std::shared_mutex>> locks;
		for (size_t i{ 0 }; i < buckets.size(); i++) {
			locks.push_back(
				std::unique_lock<std::shared_mutex>( buckets[i].mutex));
		}

		std::map<Key, Value> result;
		for (size_t i{ 0 }; i < buckets.size(); i++) {
			for (auto it = buckets[i].data.begin(); it != buckets[i].data.end(); it++) {
				result.insert(*it);
			}
		}
		return std::move(result);
	}

private:
	class bucket_type
	{
	public:
		Value value_for(const Key& key, const Value& default_val) const
		{
			// TODO: тут предполагается rw mutex - так ли это сейчас ?

			std::shared_lock<std::shared_mutex> lock(mutex);
			const bucket_iterator item = find_entry_for(key);
			return item == data.end() ? default_val : item->second;
		}

		void add_or_update_mapping(const Key& key, const Value& val)
		{
			std::unique_lock<std::shared_mutex> lock(mutex);
			auto item = find_entry_for(key);
			if (item == data.end()) {
				data.push_back({ key,val });
			} else {
				item->second = val;
			}			
		}

		void remove_mapping(const Key& key)
		{
			std::unique_lock<std::shared_mutex> lock(mutex);
			auto item = find_entry_for(key);
			if (item != data.end())
				data.erase(item);
		}

	private:
		typedef std::pair<Key, Value> bucket_value;
		typedef std::list<bucket_value> bucket_data;
		typedef typename bucket_data::iterator bucket_iterator;

		bucket_data data;
		mutable std::shared_mutex mutex;

		bucket_iterator find_entry_for(Key const& key) const
		{
			return std::find_if(data.begin(), data.end(),
				[&](const bucket_value& item) { return item.first == key; });
		}
	};

	std::vector<std::unique_ptr<bucket_type>> buckets;
	Hash hasher;

	bucket_type& get_bucket(const Key& key) const
	{
		const std::size_t index = hasher(key) % buckets.size();
		return *buckets[index];
	}
};



} // namespace CDS