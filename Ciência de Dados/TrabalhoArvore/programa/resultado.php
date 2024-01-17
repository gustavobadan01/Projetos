<?php
session_start();

$resposta = $_SESSION['resposta'];

?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Trabalho de Dados</title>
  <link rel="stylesheet" href="styles.css">
</head>
<body>

  <img src="fundo.jpg" id="fundo">

  <div id="form-perguntas">
    <?php
      $respostas = '<h2>' . $resposta . '</h2>';
      echo $respostas;
    ?>
  </div>

</body>
</html>
