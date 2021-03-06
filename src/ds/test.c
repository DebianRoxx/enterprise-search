
#include <stdlib.h>
#include <stdio.h>

#include "dcontainer.h"
#include "dpair.h"
#include "dtuple.h"
#include "dvector.h"
#include "dstack.h"
#include "dqueue.h"
#include "dlist.h"
#include "dmap.h"
#include "dmultimap.h"
#include "dset.h"


void test_vmerge()
{
    container	*V = vector_empty_container( string_container() );
    void	*d = vector_new_data();
    void	*e = vector_new_data();

    vector_attach_data(V,d);
    vector_pushback(V, "alfa");
    vector_pushback(V, "beta");

    vector_attach_data(V,e);
    vector_pushback(V, "delta");
    vector_pushback(V, "gamma");
    vector_pushback(V, "foxtrot");

    vector_attach_data(V,d);
    println(V);
    vector_destroy_data(V);

    vector_attach_data(V,e);
    println(V);
    destroy(V);
}

void test_it2()
{
    container	*S = set_container( string_container() );
    set_insert(S, "shuriken");
    set_insert(S, "bo-stav");
    set_insert(S, "katana");
    set_insert(S, "sai-sverd");
    set_insert(S, "nunchaku");

    printf("Search for \"katana\" %d\n",(set_find(S, "katana")).valid);
    printf("Search for \"sai-sverd\" %d\n",(set_find(S, "sai-sverd")).valid);
    printf("Search for \"bo-stav\" %d\n",(set_find(S, "bo-stav")).valid);
    printf("Search for \"shuriken\" %d\n",(set_find(S, "shuriken")).valid);
    printf("Search for \"nunchaku\" %d\n",(set_find(S, "nunchaku")).valid);
    printf("Search for \"dont exist\" %d\n",(set_find(S, "dont exist")).valid);

    iterator2	it2 = set_begin2(S);
    for (; it2.valid; ds_next(it2)) printf("%s\n", ds_key(it2).str);

    printf("-----\n");

    it2 = set_end2(S);
    for (; it2.valid; ds_next(it2)) printf("%s\n", ds_key(it2).str);

    printf("-----\n");


    container	*T = set_container( string_container() );
    set_insert(T, "katana");
    set_insert(T, "samurai-sverd");
    set_insert(T, "nunchaku");
    set_insert(T, "sai-sverd");

    printf("S = %s\n", asprint(S,"��"));
    printf("T = ");
    println(T);

    container	*Ri = ds_intersection( set_begin2(S), set_begin2(T) );
    printf("intersection = ");
    println(Ri);
    container	*Ru = ds_union( set_begin2(S), set_begin2(T) );
    printf("union = ");
    println(Ru);

    destroy(S);
    destroy(T);
    destroy(Ri);
    destroy(Ru);
}

void test_aclset()
{

    container	*S2 = set_container( string_container() );

    set_insert(S2, "s-1-5-21-3106318878-4088633202-286446095-1148");
    set_insert(S2, "s-1-5-21-3106318878-4088633202-286446095-1115");
    set_insert(S2, "everyone");
    set_insert(S2, "s-1-5-21-3106318878-4088633202-286446095-1132");
    set_insert(S2, "searchdaimon");
    set_insert(S2, "s-1-1-0");
    set_insert(S2, "domain users");
    set_insert(S2, "demo");
    set_insert(S2, "s-1-5-21-3106318878-4088633202-286446095-513");
    set_insert(S2, "group4");
    set_insert(S2, "s-1-5-32-545");
    set_insert(S2, "demo group");
    set_insert(S2, "users");
    set_insert(S2, "s-1-5-21-3106318878-4088633202-286446095-1147");

    printf("Search for \"s-1-5-32-545\"= %d\n",(set_find(S2, "s-1-5-32-545")).valid);
    printf("Search for \"\"= %d\n",(set_find(S2, "")).valid);
    printf("Search for \"s-1-5-21-3106318878-4088633202-286446095-1132\"= %d\n",(set_find(S2, "s-1-5-21-3106318878-4088633202-286446095-1132")).valid);


}

void another_test()
{
    container	*V = vector_container( pair_container( int_container(), vector_container( string_container() ) ) );
    vector_pushback(V, 1);
    vector_pushback(V, 2);
    vector_pushback(V, 3);
    vector_pushback(V, 4);
    vector_pushback(V, 5);
    vector_pushback(V, 6);
    vector_pushback(V, 7);
    vector_pushback(V, 8);
    vector_pushback(pair(vector_get(V,0)).second.C, "en");
    vector_pushback(pair(vector_get(V,1)).second.C, "to");
    vector_pushback(pair(vector_get(V,2)).second.C, "tre");
    vector_pushback(pair(vector_get(V,3)).second.C, "fire");
    vector_pushback(pair(vector_get(V,4)).second.C, "fem");
    vector_pushback(pair(vector_get(V,4)).second.C, "fem(2)");
    vector_pushback(pair(vector_get(V,6)).second.C, "sju");
    vector_pushback(pair(vector_get(V,vector_size(V)-1)).second.C, "åtte");

    println(V);
    destroy(V);
}


void tuple_test()
{
    container	*V = vector_container( tuple_container(3, int_container(), int_container(), string_container()) );

    vector_pushback(V, 1, 2, "1+2");
    vector_pushback(V, 2, 3, "2+3");
    vector_pushback(V, 3, 4, "3+4");
    vector_remove_last(V);
    vector_pushback(V, 4, 5, "4+5");
    vector_pushback(V, 5, 6, "5+6");
    vector_pushback(V, 6, 7, "6+7");
    vector_pushback(V, 7, 8, "7+8");
    vector_remove_last(V);
    vector_pushback(V, 8, 9, "8+9");

    println(V);

    destroy(V);
}

void multimap_test()
{
    container	*M = multimap_container( int_container(), string_container() );

    multimap_insert(M, 3, "f");
    multimap_insert(M, 3, "g");
    multimap_insert(M, 2, "c");
    multimap_insert(M, 1, "a");
    multimap_insert(M, 2, "d");
    multimap_insert(M, 1, "b");
    multimap_insert(M, 2, "e");
    multimap_insert(M, 3, "h");

    println(M);

    destroy(M);
}


void list_in_list_test()
{
    container	*L = list_container( list_container( int_container() ) );
    container	*LL;

    list_pushback(L);
    LL = list_val(list_end(L)).C;
    list_pushback(LL, 1);
    list_pushback(LL, 2);
    list_pushback(LL, 3);
    list_pushback(LL, 4);

    list_pushback(L);
    LL = list_val(list_end(L)).C;
    list_pushback(LL, 5);
    list_pushback(LL, 6);
    list_pushback(LL, 7);

    iterator	it1, it2;
    it1 = list_begin(L);
    for (; it1.valid; it1=list_next(it1))
	{
	    it2 = list_begin(list_val(it1).C);
	    for (; it2.valid; it2=list_next(it2))
		printf("%i ", list_val(it2).i);
	    printf("\n");
	}

    destroy(L);
}


void map_in_list_test()
{
    container	*L = list_container( map_container( int_container(), string_container() ) );
    container	*M;

    list_pushback(L);
    M = list_val(list_end(L)).C;
    map_insert(M, 4, "bra");
    map_insert(M, 1, "abra");
    map_insert(M, 3, "da");
    map_insert(M, 2, "ka");

    list_pushback(L);
    M = list_val(list_end(L)).C;
    map_insert(M, 6, "pokus");
    map_insert(M, 7, "filiokus");
    map_insert(M, 5, "hokus");

    iterator	it1, it2;
    it1 = list_begin(L);
    for (; it1.valid; it1=list_next(it1))
	{
	    it2 = map_begin(list_val(it1).C);
	    for (; it2.valid; it2=map_next(it2))
		printf("%i ", map_key(it2).i);
	    printf("\n");
	}

    destroy(L);
}


void stack_in_vector_test()
{
    container	*V = vector_container( stack_container( int_container() ) );
    container	*S;

    vector_pushback(V);
    vector_pushback(V);
    vector_pushback(V);
    vector_pushback(V);

    S = vector_get(V,0).C;
    stack_push(S, 7);
    stack_push(S, 3);
    stack_push(S, 3);
    stack_push(S, 1);
    stack_push(S, 3);
    S = vector_get(V,1).C;
    stack_push(S, 5);
    stack_push(S, 3);
    stack_push(S, 2);
    stack_push(S, 1);
    stack_push(S, 1);
    S = vector_get(V,2).C;
    stack_push(S, 11);
    stack_push(S, 7);
    stack_push(S, 5);
    stack_push(S, 3);
    stack_push(S, 2);
    S = vector_get(V,3).C;
    stack_push(S, 4);
    stack_push(S, 2);

    int		i;
    for (i=0; i<vector_size(V); i++)
	{
	    printf(": ");
	    S = vector_get(V,i).C;
	    while (stack_size(S)>0)
		{
		    printf("%i ", stack_peak(S).i);
		    stack_pop(S);
		}
	    printf("\n");
	}

    destroy(V);
}


void list_in_map_test()
{
    container	*M = map_container( string_container(), list_container( string_container() ) );
    container	*L = list_container( string_container() ), *L2 = list_container( string_container() );

    list_pushback(L, "aaa");
    list_pushback(L, "bab");
    list_pushback(L, "cac");
    list_pushback(L, "ddd");

    map_insert_value(M, string_value("baluba"), container_value(L));

    list_pushback(L2, "555");
    list_pushback(L2, "777");
    list_pushback(L2, "999");

    map_insert_value(M, string_value("boliboli"), container_value(L2));

    iterator	mit = map_begin(M);
    for (; mit.valid; mit=map_next(mit))
	{
	    iterator	it = list_begin(map_val(mit).C);
	    for (; it.valid; it=list_next(it))
		printf("%s ", (char*)list_val(it).ptr);
	    printf("\n");
	}

    destroy(M);
}


void sorted_vector_test()
{
    container	*M = map_container( vector_container( int_container() ), string_container() );
    container	*V1 = vector_container( int_container() ),
		*V2 = vector_container( int_container() ),
		*V3 = vector_container( int_container() ),
		*V4 = vector_container( int_container() ),
		*V5 = vector_container( int_container() );

    vector_pushback(V1, 5);
    vector_pushback(V1, 4);
    vector_pushback(V1, 3);
    vector_pushback(V2, 5);
    vector_pushback(V2, 4);
    vector_pushback(V2, 2);
    vector_pushback(V3, 1);
    vector_pushback(V3, 2);
    vector_pushback(V3, 3);
    vector_pushback(V3, 4);
    vector_pushback(V4, 5);
    vector_pushback(V4, 5);
    vector_pushback(V4, 1);
    vector_pushback(V5, 5);
    vector_pushback(V5, 4);
    vector_pushback(V5, 3);
    vector_pushback(V5, 2);

    map_insert_value(M, container_value(V1), string_value("en"));
    map_insert_value(M, container_value(V2), string_value("to"));
    map_insert_value(M, container_value(V3), string_value("tre"));
    map_insert_value(M, container_value(V4), string_value("fire"));
    map_insert_value(M, container_value(V5), string_value("fem"));

    iterator	mit = map_begin(M);
    for (; mit.valid; mit=map_next(mit))
	{
	    int		i;
	    container	*V = map_key(mit).C;

	    for (i=0; i<vector_size(V); i++)
		printf("%i ", vector_get(V,i).i);
	    printf("=> %s\n", (char*)map_val(mit).ptr);
	}
    printf("\n");

    destroy(M);
}


void print_set( container *S )
{
    iterator	it = set_begin(S);
    for (; it.valid; it=set_next(it))
	{
	    printf("%i ", set_key(it).i);
	}
    printf("\n");
}


void set_test()
{
    container	*S = set_container( int_container() );

    set_insert(S, 5);
    set_insert(S, 7);
    println(S);
    set_insert(S, 2);
    set_insert(S, 3);
    println(S);
    set_insert(S, 4);
    set_insert(S, 1);
    println(S);
    set_insert(S, 8);
    set_insert(S, 7);
    println(S);

    set_remove(S, 2);
    println(S);

    set_remove(S, 5);
    println(S);

    set_insert(S, 9);
    set_insert(S, 0);
    println(S);

    set_remove(S, 0);
    set_remove(S, 3);
    set_remove(S, 12);
    set_remove(S, 4);
    set_remove(S, 4);
    println(S);

    set_remove(S, 1);
    set_remove(S, 7);
    set_remove(S, 8);
    set_remove(S, 9);
    println(S);

    destroy(S);
}


void print_map( container *M )
{
    iterator	it = map_begin(M);
    for (; it.valid; it=map_next(it))
	{
	    printf("%i ", map_key(it).i);
	}
    printf("\n");
}


void map_test()
{
    container	*M = map_container( int_container(), int_container() );

    printf("---map---\n");

    map_insert(M, 5, 0);
    println(M);
    map_insert(M, 7, 0);
    println(M);
    map_insert(M, 2, 0);
    println(M);
    map_insert(M, 3, 0);
    println(M);
    map_insert(M, 4, 0);
    println(M);
    map_insert(M, 1, 0);
    println(M);
    map_insert(M, 8, 0);
    println(M);
    map_insert(M, 7, 0);
    println(M);
    map_insert(M, 9, 0);
    println(M);
    map_insert(M, 0, 0);
    println(M);
    map_insert(M, 12, 0);
    println(M);
    map_insert(M, 3, 0);
    println(M);
    map_insert(M, 6, 0);
    println(M);

    printf("---\n");
    destroy(M);
}


/* main: */

int main()
{
    test_aclset();
exit(0);
    test_vmerge();
    //exit(0);
    test_it2();
    exit(0);

    another_test();
    tuple_test();
    multimap_test();
    sorted_vector_test();
    list_in_list_test();
    map_in_list_test();
    stack_in_vector_test();
    list_in_map_test();
    set_test();
    map_test();
    exit(0);

    container	*M = map_container( int_container(), string_container() );

    map_insert(M, 3, "tre");
    map_insert(M, 2, "to");
    map_insert(M, 8, "�tte");
    map_insert(M, 5, "fem");
    map_insert(M, 9, "ni");
    map_insert(M, 1, "en");
    map_insert(M, 4, "fire");
    map_insert(M, 7, "sju");

    iterator	mit = map_begin(M);
    for (; mit.valid; mit=map_next(mit))
	{
	    printf("%i: %s\n", map_key(mit).i, (char*)map_val(mit).ptr);
	}

    printf("---\n");

    mit = map_end(M);
    for (; mit.valid; mit=map_previous(mit))
	{
	    printf("%i: %s\n", map_key(mit).i, (char*)map_val(mit).ptr);
	}

    printf("---\n");

    value	w;
    w.i = 5;
    mit = map_find_value(M, w);
    if (mit.valid)
        printf("%i: %s\n", map_key(mit).i, (char*)map_val(mit).ptr);
    else
	printf("not found\n");

    mit = map_find(M, 3);
    if (mit.valid)
        printf("%i: %s\n", map_key(mit).i, (char*)map_val(mit).ptr);
    else
	printf("not found\n");

    //-----

    container	*L = list_container( int_container() );
    iterator	it;

    list_pushback(L, 5);
    list_pushfront(L, 3);
    list_insert(L, list_next(list_begin(L)), 4);
    list_pushback(L, 6);
    list_pushfront(L, 1);
    it = list_begin(L);
    it = list_next(it);
    list_insert(L, it, 2);

    it = list_begin(L);

    printf("list(%i): ", list_size(L));
    int		del;
    for (del=0; it.valid; del++)
	{
	    iterator	gammel_it = it;
	    printf("%i ", list_val(it).i);
	    it = list_next(it);
	    if (del&1) list_erase(L, gammel_it);
	}
    printf(" |  ");
    for (it=list_end(L); it.valid; it = list_previous(it))
	{
	    printf("%i ", list_val(it).i);
	}
    printf("\n");

    container	*I = int_container();
    value	v;

    v = allocate(I, 1);
    printf("%i\n", v.i);
    deallocate(I, v);
    destroy(I);

    container	*P = pair_container( int_container(), int_container() );

    v = allocate(P, 3, 5);
    printf("%i %i\n", pair(v).first.i, pair(v).second.i);
    deallocate(P, v);
    destroy(P);

    container	*P2 = pair_container( pair_container(int_container(), int_container()), int_container() );

    v = allocate(P2, 4, 5, 6);

    printf("%i %i %i\n",
	pair( pair(v).first).first.i,
	pair( pair(v).first).second.i,
	pair( v).second.i );

    deallocate(P2, v);
    destroy(P2);
/*
    container	*A, *B;
    value	a, b;

    A = pair_container( int_container(), pair_container( int_container(), int_container() ));
    B = pair_container( int_container(), pair_container( int_container(), int_container() ));

    a = allocate(A, 6, 5, 700);
    b = allocate(B, 6, 5, 90);

    int		ret = compare(A, a, b);

    if (ret==0)
	printf("A == B\n");
    else
	printf("A %c B\n", (ret > 0 ? '>' : '<'));
*/

    container	*V = vector_container( pair_container( string_container(), int_container() ) );
    int		i;

    vector_pushback(V, "aa", 5);
    vector_pushback(V, "b", 6);
    vector_pushback(V, "ccc", 7);
    vector_pushback(V, "defghi", 9);

    for (i=0; i<vector_size(V); i++)
	printf("%s %i\n", (char*)pair(vector_get(V, i)).first.ptr,
			pair(vector_get(V, i)).second.i );

    destroy(V);


    container	*S = stack_container( int_container() );

    stack_push(S, 6);
    stack_push(S, 5);
    stack_push(S, 3);
    stack_push(S, 4);
    stack_push(S, 2);
    stack_push(S, 1);
    stack_push(S, -8);

    while (stack_size(S)>0)
	{
	    printf("%i\n", stack_peak(S).i);
	    stack_pop(S);
	}

    destroy(S);
/*
    {
	container	*V = vector_container( int_container() );
	int		i;

	for (i=0; i<4000000; i++)
	    vector_pushback(V, i);

	for (i=0; i<vector_size(V); i++)
	    vector_get(V, i);
    }
*/

    printf("---\n");

    {
        container	*Q = queue_container( string_container() );
	int		i;

        queue_push(Q, "alfa");
        queue_push(Q, "beta");
        queue_push(Q, "3");
        queue_push(Q, "oto");
        queue_push(Q, "gamma");
        queue_push(Q, "nils");

	for (i=0; i<5; i++)
	    {
		printf("%s\n", (char*)queue_peak(Q).ptr);
		queue_pop(Q);
	    }

	queue_push(Q, "dette");
	queue_push(Q, "er");
	queue_push(Q, "noe");
	queue_push(Q, "vi");
	queue_push(Q, "la");
	queue_push(Q, "til");
	queue_push(Q, "helt");
	queue_push(Q, "p");
	queue_push(Q, "slutten");

	while (queue_size(Q)>0)
	    {
		printf("%s\n", (char*)queue_peak(Q).ptr);
		queue_pop(Q);
	    }
    }

    return 0;
}
