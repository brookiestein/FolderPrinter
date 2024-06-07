# FolderPrinter

Este programa escucha de manera activa a una carpeta del sistema que le indiques, en busca de archivos PDF. Tan pronto como copies un PDF en esa carpeta, la imprime a través de la impresora por defecto de tu sistema.

Este programa o «demonio» (del inglés «daemon») está pensando para mantenerse ejecutándose todo el tiempo.

La primera vez que lo ejecutas debes indicarle la carpeta que escuchará y nunca más te lo preguntará, a menos que esa carpeta deje de existir.

## Historia
Un amigo tenía un problema imprimiendo directamente desde el software desde el cual saca facturas. Yo tratando de ayudarlo a solucionar ese problema descubrí que es únicamente imprimiendo directamente desde ese software
hacia la impresora que hacía que saliese mal la factura, puesto que si lo imprime como PDF y con un lector de PDFs, por ejemplo el navegador web, lo podíamos imprimir sin problemas.

Lo solución más lógica era pedir soporte al depto. de TI, cierto? Pues parece que eso no iba a funcionar, así que mi propuesta hacia mi amigo fue:

_«Habla con el depto. de TI y si no te dan respuesta, avísame para yo hacerte una utilidad que te facilite el trabajo, puesto que al final del día tienes ese problema y necesita ser solucionado.»_

Así que le ofrecí que imprimiera sus facturas a la carpeta que este programa «escuchará» y sin más, este programa se la imprimirá a través de su impresora, vamos exactamente lo mismo que si él abriera el PDF
en el navegador y le diera click al botón de imprimir, PERO automatizado.

Otros nombres que le podrías dar en tu mente son: «Simulador», «Intermediario», etc.

Para mí ha sido un placer ayudar a quien lo necesita.
