# Crivo_Erastotenes_SO
Implementação de uma variação distribuída do Crivo de Erastóstenes (em inglês, Sieve of Eratosthenes), um algoritmo simples e prático para encontrar números primos no intervalo entre 2 e um dado valor limite n.


# Sobre
 O Crivo de Eratóstenes é um algoritmo e um método simples e prático para encontrar números primos
até um certo valor limite. Segundo a tradição, foi criado pelo matemático grego Erastóstenes (a.c. 285-
194 a.C.), o terceiro bibliotecário-chefe da Biblioteca de Alexandria.

Linguagem de Programação e Ferramentas:  C, usando a biblioteca Pthreads.


# Características
 Utilizando 8 threads de filtro (sieve) para testar se um número é primo ou não.
 
• Uma thread para acumular os resultados da computação e imprimí-los na tela.

• A thread principal fica responsável por gerar os números a serem testados até um certo limite n. 

As seguintes restrições se aplicam:

• As threads de sieve ficam organizadas em anel, e a comunicação entre sieves é feita somente para a seguinte no anel. Assim, a sieve 3 se comunica somente com a sieve 4 e a sieve 7 somente com a sieve 0.

• Não existe nenhuma comunicação entre qualquer thread de sieve e a thread principal, exceto quando a thread principal insere um número para teste na rede de sieves.

• Toda a comunicação entre threads é feita através de um buffer limitado a m números. Todos os buffers são protegidos por seções críticas, de forma a garantir a sua consistência.

• As threads realizam o máximo de comunicações assíncrona possível, exibindo assim o máximo grau de paralelismo. Isso implica na necessidade de admissão simultânea de vários inteiros para serem testados na rede de sieves.


O funcionamento do crivo é da seguinte forma:

• A thread principal cria as demais threads e a seguir entra em loop, gerando um a um os números no intervalo 2 até n.

• Ao gerar o número i, a thread principal o envia para a sieve 0, colocando i no buffer da sieve. Isso feito, dizemos que i foi inserido na rede de sieves para ser testado.

• Cada uma das sieves possui uma área de armazenamento (além do buffer) para guardar os primos que a sieve for identificando.

• Os números em teste na rede circulam da seguinte forma:

  - Buffers seguem uma política FIFO. Uma sieve retira o primeiro número i do buffer e testa i contra um dos primos já armazenados na sieve.
  - Se i é divisível por algum dos primos da sieve, ela envia essa informação para a thread de resultados.
  - Se i não é divisível por nenhum dos primos da sieve, ela propaga i para a próxima sieve do anel para que o número continue sendo testado. Se a rede testar i contra todos os primos anteriores a ele, o número i é declarado primo e armazenado em uma das sieves. A sieve que armazenou o número envia essa informação para a thread de resultados.
    
• O programa termina quando todos os números gerados pela thread principal forem testados pela rede.

# Exemplo
Para executar: Abra o terminal na pasta dos arquivos e dê um "make";

`./trab1 n m`

onde n é o número máximo que deve ser testado e m é o tamanho do buffers entre as threads.
A thread de resultados imprime as informações sobre cada número testado, em ordem. Assim, se o número for primo ele deve ser indicado como tal, juntamente com a sieve aonde ele ficou armazenado. Se o número não for primo, essa informação¸ também deve ser impressa. 
Dessa forma, por exemplo, se executarmos

`./trab1 10 2 `

teremos como resposta no terminal:
2 is prime (stored in sieve 0)
3 is prime (stored in sieve 1)
4 divided by 2 at sieve 0
5 is prime (stored in sieve 2)
6 divided by 2 at sieve 0
7 is prime (stored in sieve 3)
8 divided by 2 at sieve 0
9 divided by 3 at sieve 1
10 divided by 2 at sieve 0

# Colaboradores
Trabalho realizado por [Elyabe Alves](https://github.com/Elyabe), [Thayza Sacconi](https://github.com/ThayzaSacconi) e [Danielli Costa](https://github.com/daniellic9).
