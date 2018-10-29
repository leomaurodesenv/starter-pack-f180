## Exemplo   

Exemplo de como executar um código ssl-vision para "seguir a bola".   
   
---
   
Dentro do arquivo `\example\main.cpp` veja as novas funções para maior entendimento sobre o exemplo:   
* `void command(...)`: Movimenta as rodas do robo[_yellow|blue_][_id_]   
* `void MoverPara(...)`: Mando o robo[][] seguir para um ponto _(x, y)_   
   
---
   
### Instalação do Exemplo   
   
```
# 1. Entre em modo super usuário 
sudo -i # (ou, sudo su)

# 2. Acesse o ssl-vision
cd \main\ssl-vision-master\

# 3. Substitua o arquivo main.cpp
# \main\ssl-vision-master\src\client\main.cpp
# pelo arquivo exemplo '\example\main.cpp'

# 4. Construa o programa
make cleanup_cache
make

# 5. Execute o ssl-vision
.\bin\client

```
