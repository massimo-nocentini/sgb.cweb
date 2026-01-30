
docker-run:
	docker run -it --rm -v ./generated:/home/output ghcr.io/massimo-nocentini/sgb.cweb:master cp -r c pdf /home/output

docker-build:
	docker build -t ghcr.io/massimo-nocentini/sgb.cweb:master .

sgb:
	rm -rf upstream/*
	cd upstream && wget --no-verbose https://cs.stanford.edu/pub/sgb/sgb.tar.gz	
	cd upstream && wget --no-verbose https://www-cs-faculty.stanford.edu/~knuth/programs/makegraph.w
	cd upstream && wget --no-verbose https://www-cs-faculty.stanford.edu/~knuth/programs/makedigraph.w
	rm -rf src && mkdir src && cp upstream/* src/
	cd src && tar xf sgb.tar.gz && rm sgb.tar.gz
