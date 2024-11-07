const mongoose = require("mongoose");
const Schema = mongoose.Schema;

const listingSchema = new Schema({
    title: {
        type: String,
        required: true,
    },
    description: String,
    image: {
        type: String,
        default:
            "https://unsplash.com/photos/a-foggy-view-of-the-golden-gate-bridge-K2HIvGR9CPQ", // Default image URL
        set: (v) => {
            if (typeof v !== 'string') {
                // If the value is not a string, return undefined
                return undefined;
            }
            return v === "" ? undefined : v; // Set to undefined if empty string is passed
        },
    },
    price: Number,
    location: String,
    country: String,
});

const Listing = mongoose.model("Listing", listingSchema);
module.exports = Listing;
