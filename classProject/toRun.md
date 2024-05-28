```python main.py -sk sprivatekey.txt -pk spublickey.txt -r```

```python main.py -sk rprivatekey.txt -pk rpublickey.txt -r```

```python main.py -k key.txt -iv iv.txt -r```

```python main.py -p plain.txt -k key.txt -iv iv.txt -sk sprivatekey.txt -c cipher.txt```

```python main.py -p key.txt -pk rpublickey.txt -c enckey.txt```

```python main.py -p iv.txt -pk rpublickey.txt -c enciv.txt```

```python main.py -p deckey.txt -sk rprivatekey.txt -c enckey.txt```

```python main.py -p deciv.txt -sk rprivatekey.txt -c enciv.txt```

```python main.py -p decplain.txt -k deckey.txt -iv deciv.txt -c cipher.txt```

```python main.py -p decplain.txt -pk spublickey.txt -s sign.txt```