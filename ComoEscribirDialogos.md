# Cómo escribir los dialogos en dialogos.json
El json esta dividido por personajes/cosas clicables. Dentro de los NPC, estan ya dividas sus secciones para poder meter los dialogos correspondientes.
```
"Vagabundo": {
  "Presentacion": [
    "Hola soy el vagabundo",
    "encantado de conocerte"
  ],
```
Si quieres crear un elemento clicable, solo va a tener un diálogo así que se crea como si fuese otro personaje más.
```
"EsclavaRemix": [
  "Bryant myers",
  "Hoy de nuevo te voy a veeer",
  "si llama pichea el cell",
  "estamos fumando marihuana",
  "hoy seras mi esclava en el cuarto de un motel"
]
```

### Acentos
Para poner acentos hace falta poner un ' $ ' ANTES de la vocal que queremos tener con acento.
```
"Buenos d$ias" = "Buenos días"
```