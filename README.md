# Lista de funcionalidades

- [x] Mostrar entrada mientras espera un comando nuevo
- [x] Manejo de un historial funcional
- [x] Buscar y ejecutar el ejecutable correcto
- [x] Interfaz bonita
- [ ] Manejo de entrada de texto:
	- [ ] No interpretar comillas sin cerrar o carácteres especificados en el enunciado como \ o ;
	- [ ] Gestional la ’ para evitar que se interpreten los metacaracteres en la secuencia entrecomillada
	- [ ] Gestionar la " para evitar que se interpreten los metacaracteres en la secuencia entrecomillada excepto $
- [x] Manejo de señales:
	- [x] ctrl-C
	- [x] ctrl-D
	- [x] ctrl-\
- [ ] Manejo de built-ins:
	- [x] echo con opción -n
	- [x] cd
	- [x] pwd
	- [ ] export
	- [ ] unset
	- [ ] env
	- [x] exit
- [x] Manejo de pipes y redirecciones:
	- [x] pipe |
	- [x] < redirige a input
	- [x] > redirige a output
	- [x] << recibe delimitador con el que leer el input
	- [x] >> redirige el output en modo append
- [ ] Variables de entorno ($):
	- [x] Variables se expanden a sus valores
	- [ ] $? se expande al estado de salida del comando mas reciente en la pipeline

# Funcionalidades bonus

- [x] Uso de && y || con paréntesis para prioridades
- [x] Uso de wildcard \* en el directorio actual
