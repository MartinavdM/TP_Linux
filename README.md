# TP_Linux

## 1. Prise en main
### 1.1 Préparation de la carte SD

### 1.2 Connection par liaison série
La première connection avec la carte se fait par laison série. À l'aide de PuTTy, une liaison est établie entre un ordianteur et le port uart (usb mini) de la carte.

Au lancement de la laison il est necessaire de se connecter avec l'identifiant et le mot de passe renseignés lors de la configuration de la carte SD. Dans notre cas:
identifiant: root
mot de passe:

Grâce à la commande `df -h`, il est possible de connaitre la taille occupée dans la carte SD. Executer cette commande permet de voir que le système de fichier n'occupe pas l'ensemble de l'espace de la carte SD. Pour remedier à cela, nous executons la commande `./expan_rootfs.sh`, puis nous lançons un reboot de la cate avec la commande `./resize2fs_once`.
## 2. Module Kernel
