<<<<<<< HEAD
#!/bin/bash

=======
#!/bin/bash                                                                                                                                                                                                 
find . -path "*/migrations/*.py" -not -name "__init__.py" -delete
find . -path "*/migrations/*.pyc"  -delete
>>>>>>> f9b3510c01c2a6f1b4cefa28cab252439c7702a8
python3 manage.py makemigrations
python3 manage.py migrate
res="$?"
while [ "$res" != "0" ]
do
    sleep 3;
    python3 manage.py migrate
    res="$?"
done
