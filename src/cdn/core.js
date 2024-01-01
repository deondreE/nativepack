/**
 * Send a get request to a given route.
 * @param {string} url
 */
const get = async (url) => {
  await fetch(url)
    .then((response) => response)
    .catch((err) => console.error(err));
};

/**
 * Send a post request to a given route.
 * @param {string} url
 * @param {*} body
 */
const post = async (url, body) => {
  await fetch(url)
    .then((response) => response)
    .catch((err) => console.error(err));
};

/**
 * append to the DOM.
 * @param {*} item item to append to the DOM.
 * @param {*} element item to append to.
 */
const append = (item, element) => {};

module.exports = { get, post, append };
