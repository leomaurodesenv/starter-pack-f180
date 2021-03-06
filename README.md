# Starter Pack F180 (Futebol CPPP/CBR)   

Este repositório serve como base de programação para entusiastas e amantes de código que querem competir na [RoboCup Small Size (F180)](http://www.cbrobotica.org/?page_id=104&lang=pt).   
   
Nele está contido um instalador automático para os programas [_grSim_](http://link.springer.com/chapter/10.1007/978-3-642-32060-6_38) e [_SSL-Vision_](https://github.com/RoboCup-SSL/ssl-vision), bem como um exemplo de integração entre eles.   
   
_No RoboCup Small Size Soccer, também conhecida como RoboCup F-180, duas equipes de 6 robôs de até 150mm de altura e com até 180 milímetros de diâmetro, disputam uma partida de futebol. Os robôs podem ser controlados remotamente por um computador, ou podem usar o processamento embarcado._
   
___
   

### Conteúdo   
   
* Instalador base do _grSim_ e _SSL-Vision_;   
* Exemplo de integração, veja _\example\how-to.md_
   
### Instalação

Shell de instalação se encontra na pasta `\install-basic\`   
_Obs: Apenas foi testado no Ubuntu 10.04 e 12.04 (recomendado)_   
   
```
# 1. Acesse a pasta raiz dos arquivos
# 2. Acesse a pasta \install-basic\
cd \install-basic\
# 3. Instale o QtCreator (opcional)
sh install-qt-linux.sh
# 4. Instale o starter-pack
sh install-f180.sh
```   

* Uma pasta `\main\` será criada, contendo o _grSim_ e o _ssl-vision-master_;
* Construa o programa e execute o `\main\grSim\bin\grSim` e o `\main\ssl-vision-master\bin\client`;
* Para testar modifique a porta para 10006 na aplicação do _grSim_, feche e reabra.
   
### Como construir o programa?   
   
```
# Acesse a raiz \main\grSim\ execute os comandos abaixo
# Repita o processo na pasta \main\ssl-vision-master\

make cleanup_cache
make
```
   
### Exemplo   

Veja o [_\example\how-to.md_](https://github.com/leomaurodesenv/starter-pack-f180/blob/master/example/how-to.md) dentro desse repositório.   
   
___
   
## Also look ~  	
* [License MIT](https://opensource.org/licenses/MIT)
* Create by Leonardo Mauro (leo.mauro.desenv@gmail.com)
* Git: [leomaurodesenv](https://github.com/leomaurodesenv/)
* Site: [Portfolio](http://leonardomauro.com/portfolio/)
