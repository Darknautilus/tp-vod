----------------------------------------------------------------
SERVEUR VOD - BINOME B3208 - BERTRON AURELIEN / PARISSE ALICIA
----------------------------------------------------------------

		- Description du projet : 
					Création d'un serveur de Vidéo à la Demande gérant plusieurs protocoles
		
		- Protocoles à gérer : 
					-> TCP PUSH
					-> TCP PULL
					-> UDP PUSH
					-> UDP PULL
					-> IP MCAST
	
		- Format d'image supportés : 
					-> BMP
					-> JPEG

		- Instructions de compilation :
				Pour compiler le serveur et générer l'exécutable il faut se positionner dans le répertoire contenant les fichiers sources et lancer la commande 
						> make
		
		- Lancement du serveur :
				L'exécutable généré se trouve dans le répertoire bin/. Pour lancer le serveur il suffit de lancer la commande
						> ./bin/insavod

		- Clients : 
				Ce serveur a été testé avec les clients fournis au cours du TP, tout particulièrement LinuxWindowsMac et VideoClient (sous wine). 
