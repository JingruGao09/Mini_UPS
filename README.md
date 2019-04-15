# Mini_UPS

#DB Setup

run command 'psql -U postgres'

In postgres:

'CREATE DATBASE "UPS";'

quit the postgres

#In Django:
    go to manage.py directory

    run 'find . -path "*/migrations/*.py" -not -name "__init__.py" -delete'
        'find . -path "*/migrations/*.pyc"  -delete'
        'python3 manage.py makemigrations'
        'python3 manage.py migrate'

