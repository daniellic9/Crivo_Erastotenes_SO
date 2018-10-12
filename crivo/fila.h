/* Universidade Federal do Espírito Santo - Ufes
   Centro Universitário Norte do Espírito Santo - Ceunes
   Sistemas Operacionais 2018/1 - TG20181
   
   Estrutura e operações de fila 

   Data: XX/03
   Autores: Elyabe Alves / Danielli Costa / Thayza sacconi

*/


// Define as operações com bits - usando um lu_t como vetor de bits
#define bit_func(a,b,op) \
 ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))


typedef struct fila
{
	lu_t *elemento, back, size, qtd_ocupado, front;
	
	pthread_mutex_t mutex_fila;
	sem_t sm_fila_livre, sm_fila_ocupada;
} Fila;

// Cria e retorna uma fila 
// size : capacidade de armazemaneto da fila
Fila* criar_fila( long unsigned size )
{
	Fila *nova_f = (Fila*)malloc(sizeof(Fila));
	if ( nova_f ) 
	{
		nova_f -> elemento = (lu_t*)malloc( size*sizeof(lu_t) );
		nova_f -> front = 0;
		nova_f -> size = size;
		nova_f -> back = nova_f -> qtd_ocupado = 0;
		pthread_mutex_init( &( nova_f -> mutex_fila ), NULL );
		// sem_init( &(nova_f -> sm_fila_livre), 0, size );
		// sem_init( &(nova_f -> sm_fila_ocupada), 0, 0 );
	} else
		exit(0);
	return nova_f;	
}

// Desaloca a fila associada ao ponteiro f
void destruir_fila( Fila **f )
{
	free( (*f) -> elemento );
	free( *f );
	*f = NULL;
}

// Retorna 1 se a fila estiver cheia e 0 caso contrário
short int fila_cheia( Fila *f )
{
	int x;
	// return ( f && f -> front >= 0 && ( f -> back ) % f -> size == (f -> front ) % f -> size && f -> back > f -> front );
	// pthread_mutex_lock( &( f -> mutex_fila ) );
		x = f -> qtd_ocupado == f -> size ;
	// pthread_mutex_unlock( &( f -> mutex_fila ) );

	return  x;
}

// Retorna 1 se a fila estiver vazia ou 0 caso contrário
short int fila_vazia( Fila *f )
{
	// return ( f && f -> front < 0 || f -> back  ==  f -> front ) ;
	int x;
	// pthread_mutex_lock( &( f -> mutex_fila ) );
		x = f -> qtd_ocupado == 0;
	// pthread_mutex_unlock( &( f -> mutex_fila ) );	

	return x;
}


// Insere elemento no final da fila
// f : Fila 
// novo_elemento : elemento a ser inserido
Fila* push_back( Fila *f, lu_t novo_elemento )
{

	if ( !fila_cheia( f )  )
	{	
		pthread_mutex_lock( &( f -> mutex_fila ) );
					f -> elemento[ f -> back % f -> size ] = novo_elemento;
					f -> back++;
					f -> qtd_ocupado++;
				// if ( f -> front < 0 ) f -> front++;
		pthread_mutex_unlock( &( f -> mutex_fila ) );
	}
	return f;
}

// Remove, se existir, o primeiro elemento da fila
// f: Fila 
lu_t pop( Fila *f )
{
	lu_t elem_removido = -1;
	if ( !fila_vazia(f) )
	{	
		pthread_mutex_lock( &( f -> mutex_fila ) );
			// if ( ( f -> front + 1) % f -> size == f -> back  ) 
			elem_removido = f -> elemento[ f -> front++ ];
			f -> qtd_ocupado--;
		pthread_mutex_unlock( &( f -> mutex_fila ) );
	}
	return elem_removido;
}

// Exibe os elementos da fila 
// f : fila 
void exibir_fila( Fila *f )
{
	long unsigned int m;

	if ( !fila_vazia(f) )
	for ( m = f -> front;  m < f -> back; m++ )
		printf(" %llu ", f -> elemento[ m % f -> size ] );
	printf("\nSTTS: %d vazia  %d cheia \n", fila_vazia(f), fila_cheia(f) );
}