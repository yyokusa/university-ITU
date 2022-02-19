'use strict';

class Form extends React.Component {
      initialState = {
        name: '',
        hdi_rank: '',
      }

      state = this.initialState

      handleChange = (event) => {
        const {name, value} = event.target

        this.setState({
          [name]: value, // !!!
        })
      }

      submitForm = () => {
        this.props.handleSubmit(this.state) // sends character object as parameter
        this.setState(this.initialState) // clear inputs
      }


      render() {
        const { name, hdi_rank } = this.state;

        return (
          <form>
            <input
              type="text"
              name="name"
              id="name"
              value={name}
              placeholder="Coutry name"
              onChange={this.handleChange} />
            <input
              type="text"
              name="hdi_rank"
              id="hdi_rank"
              value={hdi_rank}
              placeholder="HDI rank"
              onChange={this.handleChange} />
            <input type="button" value="Submit" onClick={this.submitForm} />
          </form>
        );
      }
    }

class App extends React.Component {

  handleSubmit = (country) => {
    console.log('Trying to post ' + country.name + ' ' +  country.hdi_rank);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", "http://127.0.0.1:5000/add_country", true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.send(JSON.stringify({
        'name': country.name,
        'hdi_rank': country.hdi_rank
    }));

    //   return (async () => {
          // const rawResponse = await fetch('http://127.0.0.1:5000/add_country', {
          //   method: 'POST',
          //   headers: {
          //     'Accept': 'application/json',
          //     'Content-Type': 'application/json'
          //   },
          //   body: JSON.stringify({'name': country.name, 'hdi_rank': country.hdi_rank})
          // });
          // const content = await rawResponse.json();
          // console.log(content);
        // })();
  }

  render() {
    // const { countries } = this.state
    return (
      <div className="container">
        <Form handleSubmit={this.handleSubmit}/>
      </div>
    )
  }

}


ReactDOM.render(<App />, document.getElementById('add_country_form'))
