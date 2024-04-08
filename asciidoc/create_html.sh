#!/bin/bash

asciidoctor -a stylesheet=style.css -o dist/spec.html spec.adoc
