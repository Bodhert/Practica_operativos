# Practica_operativos
# Interpretador paralelo de BINEWE 
   ### Sistemas Operativos
  
  # INTEGRANTES:

- **ALEJANDRO CORDOBA BODHERT**
- **CRAIG DAVID CARTAGENA CASTANO**

# PROFESOR:
- **JUAN FRANCISCO CARDONA MC'CORMICK**



# UNIVERSIDAD DE EAFIT

# INGENIERIA DE SISTEMAS

# 2018

![Eafit Logo](eafit.png)



  ## DESCRIPCION DEL PROYECTO
  
  Para el proyecto final de la materia de sistemas operativos de la universidad EAFIT 2018-1 nos proponen realizar un interpretador paralelo de BINEWE, aplicando el manejo de memoria y la concurrencia.

  ## TECNOLOGIAS
  
  ![c++](cplusplus.png)

   - [C++](http://www.cplusplus.com): C++ es un lenguaje de programación diseñado a mediados de los años 1979 por Bjarne Stroustrup. La intención de su creación fue el extender al lenguaje de programación C mecanismos que permiten la manipulación de objetos.. 
   
   - [EWE](https://github.com/jfcmacro/ewe): Es un lenguaje para enseñanza.
   
   - [C++11](https://en.wikipedia.org/wiki/C%2B%2B11): C++11 es una versión del estándar del lenguaje de programación C++ aprobado por la Organización Internacional de Normalización (ISO) el 12 de agosto de 2011..   
   

   
   ## EJECUCION
   
   se ejecuta con C++11
   

  ``` $ g++ -std=c++11 -o controlewe src/main.cpp src/controlewe.cpp src/interewe.cpp -lrt -lpthread
 ```


   ## Dependencias

   Se requiere la instalación por medio del manejador de paquetes de Python, pip; diferentes bibliotecas requeridas para el correcto funcionamiento de la Script.
   
- $ #include <unistd.h>
- $ #include <sys/mman.h>
- $ #include <sys/stat.h>
- $ #include <sys/types.h>
- $ #include <fcntl.h>
- $ #include <iostream>
- $ #include <fstream>
- $ #include <iomanip>
- $ #include <sstream>
- $ #include <pthread.h>
- $ #include <iomanip>
- $ #include <iostream>
- $ #include <map>
- $ #include <vector>

   ## Funcionamiento
   
   - Se identifica en la webcam vehiculos que se esten movilizando en tiempo real
   
``` python
def license_plate_recognition():
faceCascade = cv2.CascadeClassifier('haarcascade_cars.xml')
video_capture = cv2.VideoCapture(0)
cpt = 0
```
    
   - Al indentificar un vehiculo toma la foto del vehiculo
   
  ![foto vehiculo](prueba1.jpeg)
   

   
```python
if len(photo) > 4:
 picture = "image%04i.jpg" %cpt
  cv2.imwrite(picture, frame)
  thread = multiprocessing.Process(target=amazon_aws, args=(picture,))
  thread.start()
  cpt += 1
 print("Image Written!")
 ```
         
            
            
   - Al tener la foto del vehiculo, se va identificar rectangulos en dicha foto, Se reconocen los rectangulos, se le aplica el text recognition de aws a los rectangulos detectados en la imagen.
   
   ![json](json1.png)
   
```python
      for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
         frame_copy = cv2.flip(frame, 1)
         cv2.imshow('Video', frame_copy)
         fps = video_capture.get(cv2.CAP_PROP_FPS)
         if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    video_capture.release()
    cv2.destroyAllWindows() 
   ```
    
    
 
   - Con la expresiones regulares ('([A-Z][A-Z][A-Z] [0-9][0-9][0-9])\Z') y ('([A-Z][A-Z][A-Z]-[0-9][0-9][0-9])\Z') se limita al reconocimiento de texto que identifique las placas y por ultimo, se utiliza un metodo que encuentre similitudes con la expresion regular.
   
   ![foto vehiculo](prueba3.jpeg)
   
```python
    def amazon_aws(image):
    s3=boto3.resource('s3')
    bucket='telematicaequipo3'
    s3=boto3.resource('s3')
    photo=image
    client=boto3.client('rekognition')
    s3.meta.client.upload_file(photo, bucket, photo)
    response=client.detect_text(Image={'S3Object':{'Bucket':bucket,'Name':photo}})
    textDetections=response['TextDetections']
    print("Image Processing")
    for text in textDetections:
        cadena = text['DetectedText']
        patron = re.compile('([A-Z][A-Z][A-Z] [0-9][0-9][0-9])\Z')
        patron2 = re.compile('([A-Z][A-Z][A-Z]-[0-9][0-9][0-9])\Z')
        if patron.match(cadena) or patron2.match(cadena):
            print("La placa que detecto fue: " + cadena)
    print("Finish Process") 
  ```
    
  
   
## Referencias

https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_gui/py_video_display/py_video_display.html

https://pythonprogramming.net/haar-cascade-object-detection-python-opencv-tutorial/


