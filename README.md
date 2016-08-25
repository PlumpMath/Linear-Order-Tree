# Linear Order Tree

Implement a structure that maintains a linear order tree. The structure must support the following operations :

Creates an empty linear ordered set :
```sh
o_t * create_order()
```
Inserts the key a immediately before key b in the ordered set :
```sh
void insert_before(o_t *ord, key_t a, key_t b) 
```
Inserts the key a immediately after key b in the ordered set :
```sh
void insert_after(o_t *ord, key_t a, key_t b) 
```
Inserts the key a as largest element in the ordered set :
```sh
void insert_top(o_t *ord, key_t a) 
```
Inserts the key a as smallest element in the ordered set : 
```sh
void insert_bottom(o_t *ord, key_t a)
```
Deletes the key a from the ordered set :
```sh
void delete_o(o_t *ord, key_t a)
```
Returns 1 if key a occurs before key b in the ordered set, 0 else :
```sh
int is before(o t *ord, key t a, key t b)
```
***Here key_t is a number type that allows comparisons.***
