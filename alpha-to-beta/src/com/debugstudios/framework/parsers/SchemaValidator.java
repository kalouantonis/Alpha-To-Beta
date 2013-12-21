/*
 * The MIT License (MIT)
 *
 * Copyright (c) [2013] [Antonis Kalou (kalouantonis@gmail.com)]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.debugstudios.framework.parsers;

import org.xml.sax.SAXException;

import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.io.IOException;

/**
 * Created by Antonis Kalou on 20/12/13.
 */
public class SchemaValidator
{
    /** Factory to create schemas with */
    private SchemaFactory schemaFactory;
    /** Schema to validate */
    private Schema schema;

    /**
     * Create a new schema validator.
     *
     * @param language XML language to use
     */
    public SchemaValidator(String language)
    {
        schemaFactory = SchemaFactory.newInstance(language);
    }

    /**
     * Create new schema validator.
     *
     * @param language XML language to use
     * @param schemaPath Path of schema file
     * @throws SAXException
     */
    public SchemaValidator(String language, String schemaPath) throws SAXException
    {
        this(language);

        loadSchema(schemaPath);
    }

    /**
     * Load schema file instance
     *
     * @param schemaPath Path of schema file
     * @throws SAXException
     */
    public void loadSchema(String schemaPath) throws SAXException
    {
        schema = schemaFactory.newSchema(new StreamSource(new File(schemaPath)));
    }

    /**
     * Perform validation upon an XML file.
     *
     * @param xmlSource XML File to validate
     * @throws SAXException
     */
    public void validate(String xmlSource) throws SAXException
    {
        Source sourceFile = new StreamSource(new File(xmlSource));

        Validator validator = schema.newValidator();

        try
        {
            validator.validate(sourceFile);
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
