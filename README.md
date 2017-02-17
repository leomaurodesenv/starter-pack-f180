#Starter Pack F180 (Futebol CPPP/CBR)   

Este repositório serve como base para a competição [RoboCup Small Size (F180)](http://www.cbrobotica.org/?page_id=104&lang=pt).   
_No RoboCup Small Size Soccer, também conhecida como RoboCup F-180, duas equipes de 6 robôs de até 150mm de altura e com até 180 milímetros de diâmetro, disputam uma partida de futebol. Os robôs podem ser controlados remotamente por um computador, ou podem usar o processamento embarcado._
   
___
   

###Conteúdo   
   
* Instalador base do _grSim_ e _SSL-Vision_;   
   
###Instalação

Shell de instalação se encontra na pasta `\install-basic\`   
```
# 1. Entre em modo super usuário 
sudo -i
# (ou, sudo su)

# 2. Acesse a pasta raiz dos arquivos
# Exemplo: cd \user\leomaurodesenv\f180\

# 3. Instale o QtCreator (opcional)
sh \install-basic\install-qt-linux.sh

# 4. Instale o starter-pack
sh \install-basic\install-f180.sh

```
* Uma pasta `\main\` será criada, contendo o _grSim_ e o _ssl-vision-master_;
* Execute o `\main\grSim\bin\grSim` e o `\ssl-vision-master\bin\client`;
* Para testar modifique a porta para 10006 na aplicação do _grSim_, feche e reabra.
   
___
   
## Also look ~  	
* [License MIT](https://opensource.org/licenses/MIT)
* Create by Leonardo Mauro (leo.mauro.desenv@gmail.com)
* Git: [leomaurodesenv](https://github.com/leomaurodesenv/)
* Site: [Portfolio](http://leonardomauro.com/portfolio/)
