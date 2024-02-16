foreach ($file in Get-ChildItem 'I:\My Drive\NEVER DELETE\CSProjects\Observium\Observium\*.cpp') {
    & g++ -IC:/SFML/include -c $file.FullName -o "I:\My Drive\NEVER DELETE\CSProjects\Observium\Observium\..\build\$($file.BaseName).o"
}
