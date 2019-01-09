#include <aiv_unit_test.h>
#include <hashmap.h>
//Example
// TEST(name)
// {
// 	ASSERT_THAT(condition);
// }

#define INIT_HASH_MAP_WITH_ONE_ELEMENT() \
		dictionary_t* hash_map = new_dictionary(10);\
		add_key_value_pair(hash_map,"a",(void*)10,sizeof(key_value_pair_t));\
		
TEST(creation)
{
	dictionary_t* hash_map = new_dictionary(10);
	ASSERT_THAT(hash_map);	
}	
TEST(add)
{
	INIT_HASH_MAP_WITH_ONE_ELEMENT();
	int count = get_lenght(hash_map);
	ASSERT_THAT(count == 1);
	add_key_value_pair(hash_map,"b",(void*)12,sizeof(key_value_pair_t));
	add_key_value_pair(hash_map,"c",(void*)13,sizeof(key_value_pair_t));
	count = get_lenght(hash_map);
	ASSERT_THAT(count == 3);	
}		


int main(int argc, char **argv)
{
	RUN_TEST(creation);
	RUN_TEST(add);
	PRINT_TEST_RESULTS();
	return 0;
}
