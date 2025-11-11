# Use a Node.js base image
FROM node:18-alpine

# Set the working directory
WORKDIR /app

# Copy package files and install dependencies
COPY package.json package-lock.json ./
RUN npm install

# Copy the web application files
COPY web/ ./web

# Expose the port the app runs on
EXPOSE 3000

# Command to start the web server
CMD ["npm", "run", "start:web"]
