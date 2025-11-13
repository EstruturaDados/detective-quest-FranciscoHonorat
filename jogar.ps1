# Script de inicialização do Detective Quest com display visual
# PowerShell com animação e efeitos

# Configurar codificação UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# Limpar tela
Clear-Host

# Cores
$cyan = "Cyan"
$yellow = "Yellow"
$green = "Green"
$red = "Red"
$magenta = "Magenta"

# Banner ASCII
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════════════════" -ForegroundColor $cyan
Write-Host ""
Write-Host "         ██████╗ ███████╗████████╗███████╗ ██████╗████████╗██╗██╗   ██╗███████╗" -ForegroundColor $yellow
Write-Host "         ██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██║██║   ██║██╔════╝" -ForegroundColor $yellow
Write-Host "         ██║  ██║█████╗     ██║   █████╗  ██║        ██║   ██║██║   ██║█████╗  " -ForegroundColor $yellow
Write-Host "         ██║  ██║██╔══╝     ██║   ██╔══╝  ██║        ██║   ██║╚██╗ ██╔╝██╔══╝  " -ForegroundColor $yellow
Write-Host "         ██████╔╝███████╗   ██║   ███████╗╚██████╗   ██║   ██║ ╚████╔╝ ███████╗" -ForegroundColor $yellow
Write-Host "         ╚═════╝ ╚══════╝   ╚═╝   ╚══════╝ ╚═════╝   ╚═╝   ╚═╝  ╚═══╝  ╚══════╝" -ForegroundColor $yellow
Write-Host ""
Write-Host "          ██████╗ ██╗   ██╗███████╗███████╗████████╗" -ForegroundColor $yellow
Write-Host "         ██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝" -ForegroundColor $yellow
Write-Host "         ██║   ██║██║   ██║█████╗  ███████╗   ██║   " -ForegroundColor $yellow
Write-Host "         ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║   " -ForegroundColor $yellow
Write-Host "         ╚██████╔╝╚██████╔╝███████╗███████║   ██║   " -ForegroundColor $yellow
Write-Host "          ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝   " -ForegroundColor $yellow
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════════════════" -ForegroundColor $cyan
Write-Host ""
Write-Host "                 🕵️  MISTÉRIO NA MANSÃO ABANDONADA  🕵️" -ForegroundColor $magenta
Write-Host ""
Write-Host "                      Desenvolvido por: Enigma Studios" -ForegroundColor $green
Write-Host "                      Versão: 1.0 - Novembro 2025" -ForegroundColor $green
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════════════════" -ForegroundColor $cyan
Write-Host ""

# Animação de loading
Write-Host "                     Carregando" -NoNewline -ForegroundColor $yellow
for ($i = 0; $i -lt 5; $i++) {
    Start-Sleep -Milliseconds 300
    Write-Host "." -NoNewline -ForegroundColor $yellow
}
Write-Host " ✓" -ForegroundColor $green
Write-Host ""

# Verificar se executável existe
if (-not (Test-Path "bin\detective_quest.exe")) {
    Write-Host "===============================================================" -ForegroundColor $red
    Write-Host "                 ERRO: Jogo nao encontrado!                    " -ForegroundColor $red
    Write-Host "        Execute 'compilar.ps1' ou 'make' primeiro              " -ForegroundColor $red
    Write-Host "===============================================================" -ForegroundColor $red
    Write-Host ""
    pause
    exit 1
}

# Mensagem de início
Write-Host "===============================================================" -ForegroundColor $cyan
Write-Host "                  INICIANDO O JOGO...                          " -ForegroundColor $yellow
Write-Host "===============================================================" -ForegroundColor $cyan
Write-Host ""
Start-Sleep -Seconds 1

# Executar o jogo
& ".\bin\detective_quest.exe"

# Mensagem de encerramento
Write-Host ""
Write-Host ""
Write-Host "===============================================================" -ForegroundColor $cyan
Write-Host "                  OBRIGADO POR JOGAR!                          " -ForegroundColor $green
Write-Host "             Ate a proxima investigacao!                       " -ForegroundColor $green
Write-Host "===============================================================" -ForegroundColor $cyan
Write-Host ""
pause
