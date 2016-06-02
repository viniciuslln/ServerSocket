# ServerSocket
Trabalho de Redes1, um servidor que envia informações para clientes na rede

Servidor multicliente simples que recebe comandos do cliente (https://github.com/viniciuslln/ClientSocket) e envia resposta como mensagens correspondentes ao comandos.

Compilando:
g++ -std=c++11 *.hpp *.cpp -o nome_do_executavel

Executando:
./nome_do_executavel
ou caso deseje informar a porta a ser usada
./nome_do_executavel XXXX

O programa executara automaticamente e começara a escutar clientes.

O servidor usa a threads para executar separadamente cada cliente conectado.
