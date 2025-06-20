import os
import pandas as pd

# Caminho do arquivo original
caminho_arquivo = os.path.join('../datasets', 'ratings.csv')

# Verifica se o arquivo existe
if not os.path.exists(caminho_arquivo):
    raise FileNotFoundError(f"Arquivo não encontrado: {caminho_arquivo}")

# Lê o arquivo original
df = pd.read_csv(caminho_arquivo)

# Lista com os tamanhos desejados
tamanhos = [100, 1000, 10000, 100000, 1000000]

# Cria e salva os arquivos menores com apenas a coluna timestamp e sem cabeçalho
for tamanho in tamanhos:
    if tamanho <= len(df):
        df_subset = df.iloc[:tamanho][['timestamp']]
        nome_arquivo_saida = f"ratings{tamanho}.csv"
        caminho_saida = os.path.join('../datasets', nome_arquivo_saida)
        df_subset.to_csv(caminho_saida, index=False, header=False)
        print(f"Arquivo salvo: {caminho_saida}")
    else:
        print(f"Tamanho {tamanho} maior que o total de linhas disponíveis ({len(df)}). Ignorado.")
