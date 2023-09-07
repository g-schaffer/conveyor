# ==================================================================================== #
# MAKEFILE COMMANDS
# ==================================================================================== #
	
## build: build & 
.PHONY: api/build
api/build:
	@docker-compose up --build

## api/superuser: create superuser
.PHONY: api/superuser
api/superuser:
	@docker exec -it convoyor_api python manage.py createsuperuser

## api/migration: run makemigrations & migrate
.PHONY: api/migration
api/migration:
	@docker exec -it convoyor_api /bin/bash -c "python manage.py makemigrations && python manage.py migrate --traceback"

## api/dump: dump data api
.PHONY: api/dump
api/dump:
	@docker exec -it convoyor_api /bin/bash -c "python manage.py dumpdata > db_dumped.json"

## api/fixture: dump data api
.PHONY: api/fixture
api/fixture:
	@docker exec -it convoyor_api /bin/bash -c "python manage.py loaddata db.json"

## load test data and run test
.PHONY: test
test:
	@docker exec -it convoyor_api /bin/bash -c "python manage.py loaddata ./convoyeur/fixture_test.json" && cd esApp && pio test -v
	


