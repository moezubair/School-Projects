#!/usr/bin/python
import re
import sys

def identifier(scanner, token): 
    return "id", token
    
def operator(scanner, token):   
    return "operator", token
    
def digit(scanner, token):     
    return "int", token
    
def decimal(scanner, token):
    return "float", token

def main():
    scanner = re.Scanner([
        (r"[a-zA-Z_]\w*", identifier),
        (r"\+|\-|\\|\*|\=", operator),
        (r"\d+.\d+", decimal),
        (r"[0-9]+", digit),
        (r"\s+", None),
        ])
     
    tokens, remainder = scanner.scan("7 + nine - 1.0")
    
    for token in tokens:
        print token
    
main()
