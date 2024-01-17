<?php
session_start();

if (isset($_POST['reset'])) {
  session_unset();
  session_destroy();
  $_SESSION = array();
}

if (!isset($_SESSION['pergunta_atual'])) {
  $_SESSION['pergunta_atual'] = 1;
  $_SESSION['caminho'] = 'M';
}

$perguntaAtual = $_SESSION['pergunta_atual'];
$caminho = $_SESSION['caminho'];

$perguntas = array(
  1 => array(
    "M" => "Tipo de dor no peito, 0-angina típica, 1-atípica angina, 2-dor não anginosa, 3-assintomática",
    "proximo" => 2,
  ),
  2 => array(
    "E" => "Número de grandes vasos (0-3)",
    "D" => "Idade",
    "proximo" => 3,
  ),
  3 => array(
    "exang" => "angina induzida por exercício ? 1-SIM / 2-NÃO ",
    "trtbps1" => "pressão arterial em repouso mm/Hg ( 0 - 200 )",
    "trtbps2" => "pressão arterial em repouso mm/Hg ( 0 - 200 )",
    "oldpeak" => "Depressão do segmento ST induzida por exercício em relação ao repouso  (0-5.6)",
    "proximo" => 4,
  ),
  4 => array(
    "thalach1" => "Frequência cardíaca máxima alcançada",
    "thalach2" => "Frequência cardíaca máxima alcançada",
    "age" => "Idade",
    "trtbps1" => "pressão arterial em repouso mm/Hg ( 0 - 200 )",
    "trtbps2" => "pressão arterial em repouso mm/Hg ( 0 - 200 )",
    "cholE" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "cholD" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "proximo" => 5,
  ),
  5 => array(
    "cp" => "Tipo de dor no peito, 0-angina típica, 1-atípica angina, 2-dor não anginosa, 3-assintomática",
    "caa" => "Número de grandes vasos (0-3)",
    "thall" => "Anemia do Mediterrâneo, 0 = sem dados, 1 = defeito corrigido, 2 = Normal, 3 = defeito reversível",
    "chol1" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "chol2" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "chol3" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "oldpeak" => "Depressão do segmento ST induzida por exercício em relação ao repouso  (0-5.6)",
    "proximo" => 6,
  ),
  6 => array(
    "thalach" => "Frequência cardíaca máxima alcançada",
    "thall" => "Anemia do Mediterrâneo, 0 = sem dados, 1 = defeito corrigido, 2 = Normal, 3 = defeito reversível",
    "age1" => "Idade",
    "age2" => "Idade",
    "age3" => "Idade",
    "chol1" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "chol2" => "colesterol em mg/dl obtido através do sensor   (0 - 600)",
    "proximo" => 7,
  ),
  7 => array(
    "exang" => "angina induzida por exercício ? 1-SIM / 2-NÃO ",
    "age1" => "Idade",
    "age2" => "Idade",
    "age3" => "Idade",
    "age4" => "Idade",
    "proximo" => 8,
  ),
  8 => array(
    "age" => "Idade",
    "trtbps" => "pressão arterial em repouso mm/Hg ( 0 - 200 )",
    "proximo" => 9,
  ),
  9 => array(
    "age" => "Idade",
    "proximo" => 10,
  )
);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  if (isset($_POST['resposta'])) {
      $resposta = $_POST['resposta'];
      $_SESSION['respostas'][] = $resposta;

      if ($perguntaAtual == 1) {
          if ($resposta > 0) {
              $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
              $_SESSION['caminho'] = 'D';
          } else {
              $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
              $_SESSION['caminho'] = 'E';
          }
      } elseif ($perguntaAtual == 2){

        if ($resposta > 0 && $caminho == 'E') {
            $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
            $_SESSION['caminho'] = 'trtbps2';
        }else{
            $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
            $_SESSION['caminho'] = 'exang';
        }

        if ($resposta > 56 && $caminho == 'D') {
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'trtbps1';
        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'oldpeak';
        }

      } elseif ($perguntaAtual == 3) {

        if ($resposta > 138 && $caminho == 'trtbps1') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'thalach1';

        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'trtbps1';
        }

        if ($resposta > 3.5 && $caminho == 'oldpeak') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'trtbps2';
        }

        if ($resposta > 108 && $caminho == 'trtbps2') {
          
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'cholD';

        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'cholE';
        }

        if ($resposta > 0 && $caminho == 'enxg') {
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'thalachh2';
        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age';
        }
        
      } elseif ($perguntaAtual == 4) {

        if ($resposta > 150 && $caminho == 'thalach1') {
            $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
            header('Location: resultado.php');
            exit();
        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'chol1';
          
        }

        if ($resposta > 120 && $caminho == 'trtbps1') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'caa';
         
        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'cp';
        }

        if ($resposta > 172 && $caminho == 'trtbps2') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'thall';
        }

        if ($resposta > 300 && $caminho == 'cholD') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'chol2';

        }else{

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 233 && $caminho == 'cholE') {
          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 146 && $caminho == 'thalach2') {
    
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'oldpeak';

        }else{
        
          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
          
        }

        if ($resposta > 41 && $caminho == 'age') {
    
          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'chol3';

        }else{
        
          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
          
        }


      } elseif ($perguntaAtual == 5) {

        if ($resposta > 270 && $caminho == 'chol1') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'thalachh';
          
        }

        if ($resposta > 2 && $caminho == 'caa') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'chol1';
          
        }


        if ($resposta > 1 && $caminho == 'cp') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age1';
          
        }

        if ($resposta > 2 && $caminho == 'thall') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age2';

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'chol2';
          
        }

        if ($resposta > 303 && $caminho == 'chol2') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
          
        }


        if ($resposta > 0.6 && $caminho == 'oldpeak') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age3';
          
        }

        if ($resposta > 234 && $caminho == 'chol3') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'thall';

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }





        
      } elseif ($perguntaAtual == 6) {

        if ($resposta > 148 && $caminho == 'thalachh') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'enxag';
        }

        if ($resposta > 208 && $caminho == 'chol1') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age1';
        }


        if ($resposta > 62 && $caminho == 'age1') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 50 && $caminho == 'age2') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age2';
        }

        if ($resposta > 149 && $caminho == 'chol2') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age3';
        }

        
        if ($resposta > 35 && $caminho == 'age3') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maenor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }


        if ($resposta > 2 && $caminho == 'thall') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age4';
        }

      } elseif ($perguntaAtual == 7) {

        if ($resposta > 0 && $caminho == 'enxag') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 59 && $caminho == 'age1') {

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 42 && $caminho == 'age2') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'trtbps';

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 44 && $caminho == 'age3') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }

        if ($resposta > 59 && $caminho == 'age4') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age';

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        }


      } elseif ($perguntaAtual == 7) {


        if ($resposta > 101 && $caminho == 'trtbps') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        } 

        if ($resposta > 61 && $caminho == 'age') {

          $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
          $_SESSION['caminho'] = 'age';

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        } 

      } elseif ($perguntaAtual == 8) {


        if ($resposta > 61 && $caminho == 'age') {

          $_SESSION['resposta'] = 'Com menor chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();

        }else{

          $_SESSION['resposta'] = 'Com maior chance de ataque cardíaco';
          header('Location: resultado.php');
          exit();
        } 

      }
  }

  if ($perguntaAtual < count($perguntas)) {
    $_SESSION['pergunta_atual'] = $perguntas[$perguntaAtual]["proximo"];
  }

  header('Location: index.php');
  exit();
}

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
      $pergunta = '<h2 style=" color: purple; "> Pergunta Atual ' . $perguntaAtual . '</h2>';
      echo $pergunta;
    ?>
    <?php
      $questao = '<h2>' . $perguntas[$perguntaAtual][$caminho] . '</h2>';
      echo $questao;
    ?>
    <form action="index.php" method="post">
      <input type="text" id="resposta" name="resposta" required autocomplete="off" placeholder="Resposta">
      <button type="submit">Enviar Resposta</button>
    </form>
  </div>

  <div>
    <form action="index.php" method="post">
      <input type="hidden" name="reset" value="true">
      <button type="submit">Começar Novamente</button>
    </form>
  </div>

</body>
</html>
