# Language_Identifier : Getting Started

A C library that can determine the language of text

This library was my solution to a data clustering contest [Telegram Data Clustering Contest 2021 ](https://contest.com/docs/dc2021-r1) - check it out.

## Running Locally

The library was tested on servers running Debian GNU/Linux 10 (buster), x86-64 with 8 cores and 16 GB RAM and will work correctly on any clean system.
Use the following commands to build the library:

```sh
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
```



```sh
$ git clone https://github.com/heroku/python-getting-started.git
$ cd python-getting-started

$ python3 -m venv getting-started
$ pip install -r requirements.txt

$ createdb python_getting_started

$ python manage.py migrate
$ python manage.py collectstatic

$ heroku local
```





Your app should now be running on [localhost:5000](http://localhost:5000/).

## Deploying to Heroku

```sh
$ heroku create
$ git push heroku main

$ heroku run python manage.py migrate
$ heroku open
```
or

[![Deploy](https://www.herokucdn.com/deploy/button.svg)](https://heroku.com/deploy)

## Documentation

For more information about using Python on Heroku, see these Dev Center articles:

- [Python on Heroku](https://devcenter.heroku.com/categories/python)
