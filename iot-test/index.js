let express = require('express');
let bodyParser = require('body-parser');
let app = express();
app.use(bodyParser.urlencoded({ extended: false }));

app.post('/', function (req, res) {
  console.log(req.body.temp);
  res.send('ok').end();
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});
