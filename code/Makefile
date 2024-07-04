
## Project build environment ----------------------------------------------------------------------
.PHONY: docker-build docker-run docker-connect
## Build the docker image
docker-build:
	docker build -t environment/avs .

## Mount host file system and run the docker image
docker-run:
	docker run --rm -it -v "$(PWD):/home/dev" --name environment-avs environment/avs:latest

## Connect to the running container in a separate bash session
docker-connect:
	docker exec -it environment-avs /bin/bash
