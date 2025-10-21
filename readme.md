# Aula_APIS — README

Resumo rápido para deixar o projeto pronto e executar o servidor de exemplo (cpp-httplib).

## Requisitos
- MSYS2 (UCRT64) ou um toolchain g++ compatível no Windows
- Opcional (para HTTPS): OpenSSL via pacman

## Preparar ambiente (MSYS2 UCRT64)
Abra o MSYS2 UCRT64 shell e execute:
```powershell
pacman -Syu          # pode pedir para fechar/reabrir o shell
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-openssl
```

## Instalar a biblioteca (single-header)
No PowerShell (ou no shell do projeto):
```powershell
# no diretório do projeto
mkdir include -Force
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h" -OutFile .\include\httplib.h
```

## Compilar e executar (HTTP)
No MSYS2 UCRT64 shell ou PowerShell (garanta que esteja a usar o g++ do MSYS2):
```bash
g++ -std=c++17 main.cpp -Iinclude -D_WIN32_WINNT=0x0A00 -DWINVER=0x0A00 -o app.exe -lws2_32
./app.exe
```

## Compilar com HTTPS (opcional)
Se usar funcionalidades HTTPS de `httplib` instale OpenSSL (pacman acima) e link:
```bash
g++ -std=c++17 main.cpp -Iinclude -D_WIN32_WINNT=0x0A00 -DWINVER=0x0A00 -o app.exe -lws2_32 -lssl -lcrypto
```
Obs: terá de fornecer certificados no código para habilitar HTTPS no servidor.

## Testar endpoints
Em outro terminal:
```bash
curl http://localhost:8080/
curl -X POST -d "hello" http://localhost:8080/echo
```

## Integração com VS Code
- Adicione `${workspaceFolder}/include` em `.vscode/c_cpp_properties.json` (includePath).
- Use o task abaixo em `.vscode/tasks.json` para compilar automaticamente:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "shell",
      "label": "build mockapi",
      "command": "C:\\msys64\\ucrt64\\bin\\g++.exe",
      "args": [
        "-std=c++17",
        "-D_WIN32_WINNT=0x0A00",
        "-DWINVER=0x0A00",
        "${workspaceFolder}\\main.cpp",
        "-I${workspaceFolder}\\include",
        "-o",
        "${workspaceFolder}\\app.exe",
        "-lws2_32"
      ],
      "group": { "kind": "build", "isDefault": true },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

## Problemas comuns
- Erro `asio.hpp / boost` — não se aplica a este exemplo (usa cpp-httplib single-header). Se usar outras libs, instale via pacman ou vcpkg.
- Erros de linker com `__imp_*` → não esqueça `-lws2_32` no Windows.
- Se o compilador não for o do MSYS2, abra o UCRT64 shell para garantir PATH correto.
